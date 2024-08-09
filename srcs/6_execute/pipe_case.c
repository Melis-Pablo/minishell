/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:28:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 15:33:04 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**combine_cmd_args(t_cmd *cmd)
{
	char	**cmd_args;
	int		i;

	i = 0;
	while (cmd->args[i])
		i++;
	cmd_args = malloc(sizeof(char *) * (i + 2));
	if (!cmd_args)
		return (NULL);
	i = 0;
	cmd_args[i] = ft_strdup(cmd->cmd);
	while (cmd->args[i])
	{
		cmd_args[i + 1] = ft_strdup(cmd->args[i]);
		i++;
	}
	cmd_args[i + 1] = NULL;
	return (cmd_args);
}

int	exec_child(t_cmd *cmd, t_env *env)
{
	char	**envp;
	int		result;
	pid_t	pid;
	char	**cmd_args;

	envp = export_env(env);
	pid = fork();
	if (pid == 0)
	{
		cmd_args = combine_cmd_args(cmd);
		result = execve(cmd_args[0], cmd_args, envp);
		free_array(cmd_args);
		free_array(envp);
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
		ft_perror("pipe", 1);
	pid = fork();
	if (pid == 0)
	{
		close(pl->pipe_fd[0]);
		dup2(pl->fd_in, STDIN_FILENO);
		dup2(pl->pipe_fd[1], STDOUT_FILENO);
		if (pl->fd_in != STDIN_FILENO)
			close(pl->fd_in);
		if (pl->pipe_fd[1] != STDOUT_FILENO)
			close(pl->pipe_fd[1]);
		execute_internal(shell, cmd, status);
		exit(*status);
	}
	else
	{
		if (pl->pipe_fd[1] != -1)
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
