/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:53:30 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 15:18:00 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/types.h"

static void	restore_std_fds(int og_stdin, int og_stdout)
{
	dup2(og_stdin, STDIN_FILENO);
	dup2(og_stdout, STDOUT_FILENO);
	close(og_stdin);
	close(og_stdout);
}

int	check_input_redir(t_cmd *cmd, t_pl *pl)
{
	if (cmd->heredocs)
	{
		if (process_all_heredocs(cmd->heredocs, cmd->heredoc_count) != 0)
			return (1);
	}
	if (cmd->infiles)
	{
		pl->fd_in = redirect_inputs(cmd);
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
	t_pl	pl;
	// t_doc	here;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	//int	check_input_redir(t_cmd **cmd, t_doc *heredoc, t_pl *pl, int *len)
	if (check_input_redir(cmd, &pl) != 0)
		return (1);
	////////////////Missing file error check/////////////////////
		// if (len == 1 && (cmd->next_type == CT_REDIRECT_OUT ||
			// cmd->next_type == CT_REDIRECT_OUTAPP))
		// return (printf("minishell: syntax error -> expected outfile\n"), 1);
	pl.fd_out = og_stdout;
	while (len--)
	{
		//checl for missing command after pipe
		// if (cmd->next_type == CT_PIPE && cmd->name == NULL)
			// return (printf("minishell: syntax error -> pipe\n"), 1);
		if (exec_pipe_cmd(shell, cmd, &pl, status) != -1)
			break ;
	}
	restore_std_fds(og_stdin, og_stdout);
	//clear_heredocs(&here)
	return (*status);
}

int	execute_internal(t_shell *shell, t_cmd *cmd, int *status)
{
	char	*path;

	if (builtins_caller(shell, cmd, status)) //check_builtin
		return (0);
	path = get_exec_path(cmd->cmd, shell->env);
	if (path)
	{
		free(cmd->cmd);
		cmd->cmd = path;
		merge_args(cmd);
		*status = exec_child(cmd, shell->env);
		return (0);
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd("\n", 2);
	*status = 127;
	return (1);
}

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	execute(t_shell *shell, char *line, int *status)
{
	t_cmd	*cmd;
	int		result;

	if (!line || !*line)
		return (0);
	cmd = builder(line);
	if (!cmd)
	{
		*status = 1;
		return (1);
	}
	result = exec_pipeline(shell, cmd, status, count_commands(cmd));
	free_cmds(cmd);
	return (result);
}
