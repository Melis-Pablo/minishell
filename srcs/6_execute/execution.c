/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:53:30 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 16:27:38 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	restore_std_fds(int og_stdin, int og_stdout)
{
	dup2(og_stdin, STDIN_FILENO);
	dup2(og_stdout, STDOUT_FILENO);
	close(og_stdin);
	close(og_stdout);
}

int	check_input_redir(t_cmd *cmd, t_pl *pl)
{
	if (cmd->infiles)
	{
		pl->fd_in = redirect_inputs(cmd);
		if (pl->fd_in == -1)
			return (1);
		if (pl->fd_out == -1)
			return (1);
	}
	else
		pl->fd_in = STDIN_FILENO;
	return (0);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd, int *status, int len)
{
	int		og_stdin;
	int		og_stdout;
	t_pl	*pl;

	pl = (t_pl *)malloc(sizeof(t_pl));
	if (!pl)
		return (1);
	pl->fd_in = STDIN_FILENO;
	pl->fd_out = STDOUT_FILENO;
	pl->pipe_fd[0] = -1;
	pl->pipe_fd[1] = -1;
	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	if (check_input_redir(cmd, pl) != 0)
		return (free_pl_ret(pl, 1));
	pl->fd_out = og_stdout;
	while (len--)
	{
		if (exec_pipe_cmd(shell, cmd, pl, status) != -1)
			break ;
		cmd = cmd->next;
	}
	restore_std_fds(og_stdin, og_stdout);
	free(pl);
	return (*status);
}

int	err_exec_quit(t_cmd *cmd, int *status)
{
	free_cmds(cmd);
	cleanup_heredocs(cmd);
	*status = 1;
	return (1);
}

int	execute(t_shell *shell, char *line, int *status)
{
	t_cmd	*cmd;
	int		result;

	result = 0;
	if (!line || !*line)
		return (0);
	cmd = builder(line, shell);
	if (!cmd)
		return (*status = 1);
	if (check_heredoc(cmd) != 0)
		return (err_exec_quit(cmd, status));
	if (process_all_heredocs(cmd->heredocs, cmd->heredoc_count) != 0)
	{
		ft_putstr_fd("Failed to process heredocs\n", STDERR_FILENO);
		cleanup_heredocs(cmd);
		return (1);
	}
	result = exec_pipeline(shell, cmd, status, count_commands(cmd));
	cleanup_heredocs(cmd);
	free_cmds(cmd);
	return (result);
}
