/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:53:30 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/31 18:08:44 by pmelis           ###   ########.fr       */
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



static int	check_in_redir(t_cmd *cmd, t_pl *pl, int *len)
{
	///////////////////////////////////////////////////////
	if (check_heredoc(token_list, &cmd) != 0) {
		fprintf(stderr, "Failed to handle heredocs\n");     //->putstrfd()
	
		return 1;
	}
	if (process_all_heredocs(cmd.heredocs, cmd.heredoc_count) != 0)
	{
	fprintf(stderr, "Failed to process heredocs\n");        //->putstrfd()
	cleanup_heredocs(&cmd);
	return (1);
	}
	cleanup_heredocs(&cmd);
	// Free token list///////////////
	///////////////////////////////////////////////////////////
}

int	exec_pipeline(t_cmd *cmd, int *status, int len)
{
	int		og_stdin;
	int		og_stdout;
	t_pl	pl;
	t_here	*here;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	if (check_in_redir(cmd, &pl, &len) != 0)
		return (1);
	////////////////Missing file error check/////////////////////
		// if (len == 1 && (cmd->next_type == CT_REDIRECT_OUT || \
			// cmd->next_type == CT_REDIRECT_OUTAPP))
		// return (printf("minishell: syntax error -> expected outfile\n"), 1);
	pl.fd_out = og_stdout;
	while (len--)
	{
		//checl for missing command after pipe
		// if (cmd->next_type == CT_PIPE && cmd->name == NULL)
			// return (printf("minishell: syntax error -> pipe\n"), 1);
		if (exec_pipe_cmd(cmd, &pl, status) != -1)
			break ;
	}
	restore_std_fds(og_stdin, og_stdout);
	//clear here docs (&here)
	return (*status);
}

int	execute(char *line, int *status)
{
	t_cmd	*cmd;
	int		result;

	if (!line || !*line)
		return (0);
	cmd = get_commands(line);
	if (!cmd)
	{
		*status = 1;
		return (1);
	}
	result = exec_pipeline(cmd, status, get_cmd_count(cmd));
	free_cmds(cmd);
	return (result);
}
