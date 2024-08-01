/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:06:19 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 21:09:52 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	redirect_inputs(t_cmd *cmd)
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
	return (0);
}

// int	redirect_input(t_cmd **cmd)
// {
// 	int	open_ret;

// 	(*cmd)++;
// 	open_ret = open((*cmd)->name, O_RDONLY);
// 	if (open_ret == -1)
// 	{
// 		perror((*cmd)->name);
// 		return (open_ret);
// 	}
// 	if ((*cmd)->argc > 1)
// 	{
// 		if (rearrange_cmd(*cmd) != 0)
// 			return (1);
// 	}
// 	else
// 		(*cmd)++;
// 	return (open_ret);
// }

/*
int	rearrange_cmd(t_cmd *cmd)
{
	char	**new_args;
	int		i;

	i = 1;
	free(cmd->name);
	cmd->name = ft_strdup(cmd->args[1]);
	if (!cmd->name)
		return (1);
	new_args = malloc(sizeof(char *) * cmd->argc);
	if (!new_args)
		return (1);
	while (cmd->args[i])
	{
		new_args[i - 1] = ft_strdup(cmd->args[i]);
		if (!new_args[i - 1])
			ft_free_split(new_args);
		i++;
	}
	new_args[i - 1] = NULL;
	ft_free_split(cmd->args);
	cmd->args = new_args;
	return (0);
}
*/

int	redirect_outputs(t_cmd *cmd)
{
	int		open_flags;
	int		fd;
	t_redir	*tmp_out;

	tmp_out = cmd->outfiles;
	open_flags = 0;
	while (tmp_out)
	{
		if (tmp_out->type == OUTPUT)
			open_flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			open_flags = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(tmp_out->file, open_flags, 0644);
		if (fd == -1)
			return (-1);
		close(fd);
		tmp_out = tmp_out->next;
	}
	return (open(tmp_out->file, open_flags, 0644));
}

