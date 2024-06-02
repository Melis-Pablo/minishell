/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:19:24 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 16:29:15 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/* A simple error displaying function. */
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

/* Function that will read input from the terminal and return line. */
int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

/*
#usage():		Function to display error message when arguments are wrong

#Parameters:	None

#Return value:	void

#How it works:	1. Prints an error message to stderr.
                2. Prints the correct usage of the program to stdout.
                3. Exits the program with a success status.
*/
void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

/*
#open_file():		Function to open the files with the right flags

#Parameters:		char *argv
                    int i

#Return value:		int

#How it works:		1. Opens the file specified by argv with the appropriate
						flags based on the value of i.
                    2. If the file cannot be opened, calls the error function.
                    3. Returns the file descriptor of the opened file.
*/
int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

/*
#child_process():	Child process that create a fork and a pipe, put the output
					inside a pipe and then close with the exec function. The
					main process will change his stdin for the pipe file
					descriptor.

#Parameters:		char *argv
					char **envp

#Return value:		void

#How it works:		1. Creates a child process using fork.
                    2. Sets up a pipe and redirects the output to it.
                    3. Executes the command using exec.
                    4. The main process replaces its stdin with the pipe file
						descriptor.
*/
void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/*
#here_doc():	Function who make a child process that will read from the stdin
				with get_next_line until it find the limiter word and then put
				the output inside a pipe. The main process will change his stdin
				for the pipe file descriptor. 

#Parameters:	char *limiter
                int argc

#Return value:	void

#How it works:	1. Checks if the number of arguments is less than 6, if so, calls
					the usage() function.
                2. Creates a pipe, if unsuccessful, calls the error() function.
                3. Creates a child process using fork.
                4. In the child process, it reads lines until it encounters the
					limiter, then it exits.
                5. In the parent process, it waits for the child process to
					finish, then it replaces its stdin with the pipe file
					descriptor.
*/
void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

/*
#main():		Main function that run the childs process with the right file
				descriptor or display an error message if arguments are wrong.
				It will run here_doc function if the "here_doc" string is find
				in argv[1]

#Parameters:	int argc
                char **argv
                char **envp

#Return value:	int

#How it works:	1. Checks if the number of arguments is greater than or equal
					to 5.
				2. If the first argument is "here_doc", it calls the here_doc()
					function and opens the output file.
                3. If the first argument is not "here_doc", it opens the input
					and output files and replaces its stdin with the input file
					descriptor.
                4. Runs child processes for each argument.
                5. Replaces its stdout with the output file descriptor and
					executes the last command.
                6. If the number of arguments is less than 5, it calls the
					usage() function.
*/
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	usage();
}
