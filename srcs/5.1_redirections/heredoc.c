/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:55:41 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:17:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_LINE_LEN 1024
#define MAX_HEREDOCS 100

ssize_t	ft_readlines(int fd, char *buffer, ssize_t maxlen)
{
	ssize_t	n;
	ssize_t	bytes_read;
	char	c;

	n = 0;
	if (!buffer || maxlen == 0)
		return (-1);
	bytes_read = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (n < maxlen - 1)
		{
			buffer[n++] = c;
			if (c == '\n')
				break ;
		}
		else
			break ;
		bytes_read = read(fd, &c, 1);
	}
	if (bytes_read < 0)
		return (-1);
	else if (bytes_read == 0 && n == 0)
		return (0);
	else
		buffer[n] = '\0';
	return (n);
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

int	process_single_heredoc(const char *delimiter, const char *filename)
{
	char	line[MAX_LINE_LEN];
	int		tmp_fd;
	ssize_t	len;

	tmp_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (tmp_fd < 0)
	{
		perror("open");
		return (-1);
	}
	while (1)
	{
		len = ft_readlines(STDIN_FILENO, line, sizeof(line));
		if (len < 0)
		{
			perror("ft_readlines");
			close(tmp_fd);
			return (-1);
		}
		if (len == 0)
			break ;

		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}
		if (strcmp(line, delimiter) == 0)
		{
			break ;
		}
		strcat(line, "\n");
		len++;
		if (write(tmp_fd, line, len) == -1)
		{
			perror("write");
			close(tmp_fd);
			return (-1);
		}
	}
	close(tmp_fd);
	return (0);
}

int	process_all_heredocs(t_doc *heredocs, int heredoc_count)
{
	char	buffer[MAX_LINE_LEN];
	ssize_t	len;
	int		tmp_fd;
	int		i;

	i = 0;
	len = 0;
	tmp_fd = 0;
	while (i < heredoc_count)
	{
		if (process_single_heredoc(heredocs[i].delimiter, heredocs[i].filename) != 0)
		{
			perror("Failed to process heredoc");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < heredoc_count)
	{
		tmp_fd = open(heredocs[i].filename, O_RDONLY);
		if (tmp_fd != -1)
		{
			len = read(tmp_fd, buffer, sizeof(buffer));
			while (len > 0)
			{
				// write(STDOUT_FILENO, buffer, len);
				len = read(tmp_fd, buffer, sizeof(buffer));
			}
			close(tmp_fd);
		}
		i++;
	}
	return (0);
}

char	*generate_filename(int count)
{
	int		num_digits;
	int		temp;
	int		len;
	char	*filename;

	num_digits = 1;
	temp = count;
	while (temp /= 10)
		num_digits++;
	len = 8 + num_digits + 1;  // "heredoc_" (8 Zeichen) + Ziffern + Nullterminator
	filename = (char *)malloc(len);
	if (!filename)
		return (NULL);
	// Formatierung des Dateinamens ohne snprintf
	snprintf(filename, len, "heredoc_%d", count); // Mit snprintf
	return (filename);
}

int	check_heredoc(t_cmd *cmd)
{
	t_redir	*tmp;
	t_doc	heredocs[100];
	char	*filename;

	tmp = cmd->infiles;
	cmd->heredoc_count = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (cmd->heredoc_count >= 100)
			{
				printf("minishell: too many heredocs\n");
				return (-1);
			}
			filename = generate_filename(cmd->heredoc_count);
			if (!filename)
			{
				perror("malloc filename error");
				return (-1);
			}
			heredocs[cmd->heredoc_count].filename = ft_strdup(filename);
			if (!heredocs[cmd->heredoc_count].filename)
			{
				perror("ft_strdup filename error");
				free(filename);
				return (-1);
			}
			heredocs[cmd->heredoc_count].delimiter = ft_strdup(tmp->file);
			if (!heredocs[cmd->heredoc_count].delimiter)
			{
				perror("ft_strdup delimiter error");
				free(heredocs[cmd->heredoc_count].filename);
				free(filename);
				return (-1);
			}
			free(filename);
			cmd->heredoc_count++;
		}
		tmp = tmp->next;
	}
	cmd->heredocs = (t_doc *)malloc(sizeof(t_doc) * (cmd->heredoc_count + 1));
	if (!cmd->heredocs)
	{
		perror("malloc heredoc error");
		return (-1);
	}
	memcpy(cmd->heredocs, heredocs, sizeof(t_doc) * cmd->heredoc_count);
	return (0);
}
