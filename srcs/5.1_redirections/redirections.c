/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:06:19 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 14:21:40 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_case(t_redir *tmp)
{
	int	fd;

	fd = open(tmp->file, O_RDONLY);
	if (fd == -1)
		perror("input redirection error");
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}

int	heredoc_case(t_cmd *cmd)
{
	int		fd;
	char	*herenum;
	char	*tmp_filename;

	herenum = NULL;
	tmp_filename = NULL;
	herenum = malloc(sizeof(char) * 3);
	ft_itoa(cmd->heredoc_count - 1, herenum);
	tmp_filename = ft_strjoin("heredoc_", herenum);
	free(herenum);
	fd = open(tmp_filename, O_RDONLY);
	if (fd == -1)
		perror("heredoc redirection error");
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	free(tmp_filename);
	return (fd);
}

int	redirect_inputs(t_cmd *cmd)
{
	int		fd;
	t_redir	*tmp;

	tmp = cmd->infiles;
	while (tmp)
	{
		if (tmp->type == INPUT)
			fd = input_case(tmp);
		if (tmp->type == HEREDOC)
		{
			fd = heredoc_case(cmd);
		}
		tmp = tmp->next;
	}
	return (fd);
}

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
		tmp_out = tmp_out->next;
	}
	return (fd);
}
