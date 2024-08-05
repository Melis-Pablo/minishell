/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:28:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/05 14:22:36 by pmelis           ###   ########.fr       */
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
		result = execve(cmd->cmd, cmd->args, envp);
		free_array(envp);
		// (void)	cmd;
		// result = 0;
		exit(result);
	}
	else
		waitpid(pid, &result, 0);
	result = WEXITSTATUS(result);
	free_array(envp);
	return (result);
}

int	handle_pipe_case(t_shell *shell, t_cmd *cmd, int *status, t_pl *pl)
{
	pid_t	pid;

	if (pipe(pl->pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pl->pipe_fd[0]);
		dup2(pl->fd_in, STDIN_FILENO);
		dup2(pl->pipe_fd[1], STDOUT_FILENO);
		if (pl->fd_in != STDIN_FILENO)
			close(pl->fd_in);
		close(pl->pipe_fd[1]);
		execute_internal(shell, cmd, status);
		exit(*status);
	}
	else
	{
		close(pl->pipe_fd[1]);
		pl->fd_in = pl->pipe_fd[0];
	}
	return (pl->fd_in);
}

int	handle_final_case(t_shell *shell, t_cmd *cmd, int *status, t_pl *pl)
{
	if (cmd->outfiles)
	{
		pl->fd_out = redirect_outputs(cmd);
		if (pl->fd_out == -1)
			return (pl->fd_out);
		dup2(pl->fd_out, STDOUT_FILENO);
		close(pl->fd_out);
	}
	if (cmd->cmd)
	{
		dup2(pl->fd_in, STDIN_FILENO);
		if (pl->fd_in != STDIN_FILENO)
			close(pl->fd_in);
		close(pl->fd_out);
		execute_internal(shell, cmd, status);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (*status);
}

int	exec_pipe_cmd(t_shell *shell, t_cmd *cmd, t_pl *pl, int *status)
{
	if (cmd->cmd && cmd->next)
	{
		pl->fd_in = handle_pipe_case(shell, cmd, status, pl);
		if (pl->fd_in == 1)
			return (*status);
	}
	else
	{
		*status = handle_final_case(shell, cmd, status, pl);
		return (*status);
	}
	return (-1);
}
