/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:19:51 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/09 13:10:17 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_LINE_LEN 1024
#define MAX_HEREDOCS 100

char	*generate_filename(int count)
{
	int		len;
	int		num_digits;
	int		temp;
	char	*filename;

	temp = count;
	num_digits = 1;
	while (temp > 0)
	{
		temp = temp / 10;
		num_digits++;
	}
	len = 8 + num_digits + 1;
	filename = (char *)malloc(len);
	if (!filename)
		return (NULL);
	snprintf(filename, len, "heredoc_%d", count);
	return (filename);
}

void	cleanup_heredocs(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		unlink(cmd->heredocs[i].filename);
		free(cmd->heredocs[i].filename);
		free(cmd->heredocs[i].delimiter);
		i++;
	}
	free(cmd->heredocs);
	cmd->heredocs = NULL;
	cmd->heredoc_count = 0;
}

int	read_all_heredocs(t_doc *heredocs, int heredoc_count)
{
	int	i;
	int	tmp_fd;
	int	status;

	i = 0;
	while (i < heredoc_count)
	{
		tmp_fd = open(heredocs[i].filename, O_RDONLY);
		if (tmp_fd != -1)
		{
			status = read_entire_file(tmp_fd);
			close(tmp_fd);
			if (status != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	read_entire_file(int fd)
{
	char	buffer[MAX_LINE_LEN];
	ssize_t	len;

	len = read(fd, buffer, sizeof(buffer));
	while (len > 0)
		len = read(fd, buffer, sizeof(buffer));
	return (0);
}
