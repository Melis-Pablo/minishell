/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:56:49 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/09 13:23:04 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t	ft_readlines(int fd, char *buffer, ssize_t maxlen)
{
	ssize_t	n;
	int		status;

	n = 0;
	status = check_input(buffer, maxlen);
	if (status == -1)
		return (-1);
	return (read_and_store(fd, buffer, maxlen, &n));
}

int	check_input(char *buffer, ssize_t maxlen)
{
	if (!buffer || maxlen == 0)
		return (-1);
	return (0);
}

ssize_t	read_and_store(int fd, char *buffer, ssize_t maxlen, ssize_t *n)
{
	ssize_t	bytes_read;
	char	c;

	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (*n < maxlen - 1)
		{
			buffer[(*n)++] = c;
			if (c == '\n')
				break ;
		}
		else
			break ;
		bytes_read = read(fd, &c, 1);
	}
	return (finalize_read(bytes_read, buffer, n));
}

ssize_t	finalize_read(ssize_t bytes_read, char *buffer, ssize_t *n)
{
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && *n == 0)
		return (0);
	buffer[*n] = '\0';
	return (*n);
}

int	process_single_heredoc(const char *delimiter, char *filename)
{
	int	tmp_fd;
	int	status;

	tmp_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (tmp_fd < 0)
		ft_perror("open", -1);
	status = read_and_write_heredoc(tmp_fd, delimiter);
	close(tmp_fd);
	return (status);
}
