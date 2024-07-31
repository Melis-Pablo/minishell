/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:28:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/31 18:15:16 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_child(t_cmd *cmd, t_env *env)
{
	char	**envp;
	int		result;
	pid_t	pid;

	envp = export_env(env);
	pid = fork();
	if (pid == 0)
	{
		result = execve(cmd->name, cmd->args, envp);
		exit(result);
	}
	else
		waitpid(pid, &result, 0);
	result = WEXITSTATUS(result);
	//ft_free_split(envp);
	return (result);
}

int	execute_internal(t_cmd *cmd, int *status)
{
	char	*path;

	if (builtins_caller(cmd)) //check_builtins
		return (0);
	path = get_path(cmd->name);
	if (path)
	{
		free(cmd->name);
		cmd->name = path;
		//combine argsflags
		*status = execute_command_child(cmd);
		return (0);
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd->name, 2);
	ft_putstr_fd("\n", 2);
	*status = 127;
	return (1);
}

int	handle_pipe_case(t_cmd *cmd, int *status, t_pl *pl)
{
	pid_t	pid;

	if (pipe(pl->pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pl->pipefd[0]);
		dup2(pl->fd_in, STDIN_FILENO);
		dup2(pl->pipefd[1], STDOUT_FILENO);
		if (pl->fd_in != STDIN_FILENO)
			close(pl->fd_in);
		close(pl->pipefd[1]);
		execute_internal(cmd, status);
		exit(*status);
	}
	else
	{
		close(pl->pipefd[1]);
		pl->fd_in = pl->pipefd[0];
	}
	return (pl->fd_in);
}

