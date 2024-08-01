/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:54:28 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 21:08:07 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	my_check_heredoc(t_cmd *cmd)
{
	t_redir	*tmp;
	t_doc	heredocs[100];
	int		heredoc_count;
	char	filename[20];

	tmp = cmd->infiles;
	heredoc_count = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (heredoc_count >= 100)
			{
				printf("minishell: too many heredocs\n");
				return (-1);
			}
			//snprintf(filename, sizeof(filename), "/tmp/heredoc_%d", heredoc_count);
			heredocs[heredoc_count].filename = ft_strdup(filename);
			heredocs[heredoc_count].delimiter = ft_strdup(tmp->file);
			heredoc_count++;
		}
		tmp = tmp->next;
	}
	cmd->heredocs = (t_doc *)malloc(sizeof(t_doc) * heredoc_count);
	if (!cmd->heredocs)
	{
		perror("malloc heredoc error");
		return (-1);
	}
	ft_memcpy(cmd->heredocs, heredocs, sizeof(t_doc) * heredoc_count);
	cmd->heredoc_count = heredoc_count;
	return (0);
}