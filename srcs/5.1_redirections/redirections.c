/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:06:19 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/23 07:10:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_inputs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->infiles;
	while (tmp)
	{
		if (tmp->type == INPUT)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
				perror("input redirection error");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (tmp->type == HEREDOC)
		{
			//process_heredoc(tmp->file);
			//process_all_heredocs(t_doc *heredocs, int heredoc_count);
		}
		tmp = tmp->next;
	}
}

void	redirect_outputs(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->outfiles;
	while (tmp)
	{
		if (tmp->type == OUTPUT)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				perror("output redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (tmp->type == APPEND)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				perror("append redirection error");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
}
