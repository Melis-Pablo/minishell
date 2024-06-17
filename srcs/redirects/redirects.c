/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:28:47 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 13:27:39 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Input Redirections (<)

	Multiple < Redirections:
		Example: command < infile1 < infile2
		Behavior: Only the last redirection is used, so the command will read
			input from infile2.
		Effect on First Ones: The first redirections (< infile1) have no effect
			They are ignored.

Output Redirections (> and >>)

	Multiple > Redirections:
		Example: command > outfile1 > outfile2
		Behavior: Only the last redirection is used, so the command will write
			to outfile2, truncating it before writing.
		Effect on First Ones: The first redirections (> outfile1) have no
			effect. They are ignored.

	Multiple >> Redirections:
		Example: command >> appendfile1 >> appendfile2
		Behavior: Only the last redirection is used, so the command will append
			to appendfile2.
		Effect on First Ones: The first redirections (>> appendfile1) have no
			effect. They are ignored.

	Mixing > and >>:
		Example: command > outfile >> appendfile
		Behavior: Only the last redirection is used. Here, the command will
			append to appendfile.
		Effect on First Ones: The first redirection (> outfile) has no effect.
			It is ignored.

		Example: command >> appendfile > outfile
		Behavior: Only the last redirection is used. Here, the command will write
			to outfile, truncating it before writing.
		Effect on First Ones: The first redirection (>> appendfile) has no effect
			It is ignored.

Here Document Redirections (<<)

	Mixing < and <<:
		< infile is used to redirect input from a file.
		<< delimiter is used for here documents, where a block of text is
			provided directly in the command line until the delimiter is reached.

	Example: command < infile << EOF
		Behavior: The shell processes the input redirection (< infile) first,
			setting up the input from infile. The here document (<< EOF) is
			usually processed to provide input directly on the command line,
			which conflicts with reading from a file.
		Effect: the last one is used, but everything processed before that is
			ignored.
*/

/*
handle_input_redirections():
	1. Open the file for reading.
	2. Redirect the standard input to the file.
	3. Close the file.
	4. The command will read input from the file.
*/

/*
#find_command():      Searches for the command in the PATH directories.

#Parameters:         [char *] cmd - Command to search for

#Return value:       [char *] - Full path to the command if found, NULL otherwise

#How it works:
                     1. Gets the PATH environment variable.
                     2. Splits the PATH into directories.
                     3. Constructs the full path for each directory.
                     4. Checks if the command exists and is executable.
                     5. Returns the full path if found, otherwise NULL.
*/
char *find_command(char *cmd)
{
    char    *path_env;
    char    **paths;
    char    *full_path;
    int     i;

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');  // Assume ft_split splits a string into an array of strings
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
        if (!full_path)
            return (NULL);
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free(paths);
    return (NULL);
}

/*
#redirect_input():    Redirects input files to stdin.

#Parameters:         [char **] infiles - Array of input file names

#Return value:       [void] - No return value

#How it works:
                     1. Iterate over input files.
                     2. Open each file and redirect its fd to stdin.
                     3. Close the file descriptor.
*/
void	redirect_input(char **infiles)
{
	int	fd;
	int	i;

	i = 0;
	if (infiles)
	{
		while (infiles[i])
		{
			fd = open(infiles[i], O_RDONLY);
			if (fd == -1)
				perror("input redirection error");
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
}

/*
#redirect_output():   Redirects output and append files to stdout.

#Parameters:         [char **] outfiles - Array of output file names
                     [char **] appendfiles - Array of append file names

#Return value:       [void] - No return value

#How it works:
                     1. Iterate over output files.
                     2. Open each file and redirect its fd to stdout.
                     3. Close the file descriptor.
                     4. Repeat for append files with O_APPEND flag.
*/
void	redirect_output(char **outfiles, char **appendfiles)
{
	int	fd;
	int	i;

	i = 0;
	if (outfiles)
	{
		while (outfiles[i])
		{
			fd = open(outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				perror("output redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
	i = 0;
	if (appendfiles)
	{
		while (appendfiles[i])
		{
			fd = open(appendfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				perror("append redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
}

/*
#execute_command():   Executes a single command.

#Parameters:         [t_cmd *] cmd - Command structure containing command and arguments

#Return value:       [void] - No return value (exits on failure)

#How it works:
                     1. Searches for the command in the PATH directories.
                     2. Executes the command using execve.
                     3. Prints error message and exits on failure.
*/
void	execute_command(t_cmd *cmd)
{
    char *full_path;

    full_path = find_command(cmd->cmd);
    if (!full_path)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    if (execve(full_path, cmd->args, NULL) == -1)
    {
        perror("execution error");
        exit(EXIT_FAILURE);
    }
    free(full_path);
}

/*
#close_pipes():       Closes both ends of a pipe.

#Parameters:         [int *] pipes - Array containing pipe file descriptors

#Return value:       [void] - No return value

#How it works:
                     1. Closes the read and write ends of the pipe.
*/
void	close_pipes(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

/*
#exec_cmds():         Executes a list of commands with pipes.

#Parameters:         [t_cmd *] cmd_list - Linked list of command structures

#Return value:       [int] - Return status

#How it works:
                     1. Iterates over the command list.
                     2. Sets up pipes and forks for each command.
                     3. Redirects input/output as needed.
                     4. Waits for all child processes to finish.
*/
int	exec_cmds(t_cmd *cmd_list)
{
	int		pipes[2];
	pid_t	pid;
	int		status;

	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(pipes);
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (cmd_list->prev)
				dup2(pipes[0], STDIN_FILENO);
			if (cmd_list->next)
				dup2(pipes[1], STDOUT_FILENO);
			if (cmd_list->infiles)
				redirect_input(cmd_list->infiles);
			if (cmd_list->outfiles || cmd_list->appendfiles)
				redirect_output(cmd_list->outfiles, cmd_list->appendfiles);
			execute_command(cmd_list);
		}
		if (cmd_list->prev)
			close_pipes(pipes);
		cmd_list = cmd_list->next;
	}
	while (wait(&status) > 0)
		;
	return (status);
}
