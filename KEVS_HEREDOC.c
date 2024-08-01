/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KEVS_HEREDOC.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:48:55 by mdoll             #+#    #+#             */
/*   Updated: 2024/08/01 20:14:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "pipeline.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "libft.h"

static bool	limiter_found(char *line, char *limiter)
{
	if (!line)
		return (false);
	if (ft_strcmp(line, limiter) == 0)
		return (true);
	return (false);
}

static int	create_heredoc_file(t_heredoc *doc)
{
	int	i;

	doc->fd = open("/dev/random", O_RDONLY);
	if (doc->fd < 0)
		return (1);
	read(doc->fd, doc->name + 5, 5);
	close(doc->fd);
	ft_memcpy(doc->name, "/tmp/", 5);
	i = 0;
	while (i < 5)
	{
		doc->name[i + 5] = (char)(doc->name[i + 5] % 26 + 'a');
		i++;
	}
	ft_memcpy(doc->name + 10, ".heredoc", 9);
	doc->fd = open(doc->name, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (doc->fd < 1)
		return (perror ("open"), 1);
	return (0);
}

int	here_doc(t_heredoc *doc, char *limiter, t_cmd *cmd)
{
	char		*line;

	(void)cmd;
	if (create_heredoc_file(doc) != 0)
		return (1);
	while (1)
	{
		line = readline("🤨 > ");
		if (limiter_found(line, limiter) == true)
			break ;
		write(doc->fd, line, ft_strlen(line));
		write(doc->fd, "\n", 1);
		free(line);
	}
	free(line);
	close (doc->fd);
	doc->fd = open(doc->name, O_RDONLY);
	if (doc->fd < 1)
		return (perror ("open"), 1);
	return (0);
}



void	clear_heredoc(t_heredoc *doc)
{
	if (ft_strnstr(doc->name, ".heredoc", 19) != 0)
	{
		unlink(doc->name);
		close(doc->fd);
	}
}

bool	check_for_heredoc(t_cmd *cmd, int len)
{
	while (len--)
	{
		if (cmd->next_type == CT_REDIRECT_HEREDOC)
			return (true);
		cmd++;
	}
	return (false);
}

int	init_heredoc(t_cmd **cmd, t_heredoc *doc, t_fd_pipeline *pl, int *len)
{
	while ((*cmd)->next_type != CT_REDIRECT_HEREDOC)
	{
		(*cmd)++;
		(*len)--;
	}
	if ((*cmd + 1)->name == NULL)
		return (printf("minishell: syntax error -> expected limiter\n"), 1);
	if (here_doc(doc, (*cmd + 1)->name, *cmd + 1) != 0)
		return (clear_heredoc(doc), 1);
	if ((*cmd)->name == NULL)
	{
		(*cmd)++;
		(*len) -= 2;
		if ((*cmd)->argc > 1)
		{
			if (rearrange_cmd(*cmd) != 0)
				return (1);
			(*len)++;
		}
		else
			(*cmd)++;
	}
	else
		(*len)--;
	return (pl->input_fd = doc->fd, 0);
}
