/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:50:07 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/09 15:10:22 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_LINE_LEN 1024
#define MAX_HEREDOCS 100
/*
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
	while (i++ < heredoc_count)
	{
		if (process_single_heredoc(heredocs[i].delimiter,
				heredocs[i].filename) != 0)
			ft_perror("Failed to process heredoc", -1);
	}
	i = 0;
	while (i++ < heredoc_count)
	{
		tmp_fd = open(heredocs[i].filename, O_RDONLY);
		if (tmp_fd != -1)
		{
			len = read(tmp_fd, buffer, sizeof(buffer));
			while (len > 0)
				len = read(tmp_fd, buffer, sizeof(buffer));
			close(tmp_fd);
		}
	}
	return (0);
}
*/

int	read_and_write_heredoc(int tmp_fd, const char *delimiter)
{
	char	line[MAX_LINE_LEN];
	ssize_t	len;

	while (1)
	{
		len = ft_readlines(STDIN_FILENO, line, sizeof(line));
		if (len < 0)
			ft_perror("ft_readlines", -1);
		if (len == 0)
			break ;
		if (process_line(line, &len, delimiter, tmp_fd) != 0)
			return (-1);
	}
	return (0);
}

int	process_all_heredocs(t_doc *heredocs, int heredoc_count)
{
	int	i;

	i = 0;
	while (i < heredoc_count)
	{
		process_single_heredoc(heredocs[i].delimiter, heredocs[i].filename);
		i++;
	}
	return (read_all_heredocs(heredocs, heredoc_count));
}

int	process_line(char *line, ssize_t *len, const char *delimiter, int tmp_fd)
{
	if (*len > 0 && line[*len - 1] == '\n')
	{
		line[*len - 1] = '\0';
		(*len)--;
	}
	if (strcmp(line, delimiter) == 0)
		return (1);
	strcat(line, "\n");
	(*len)++;
	if (write(tmp_fd, line, *len) == -1)
		ft_perror("write", -1);
	return (0);
}

int	init_heredoc(t_cmd *cmd, t_redir *tmp, t_doc *heredocs, char *filename)
{
	if (cmd->heredoc_count >= 100)
	{
		printf("minishell: too many heredocs\n");
		return (-1);
	}
	filename = generate_filename(cmd->heredoc_count);
	if (!filename)
		return (ft_perror("malloc filename error", -1));
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
	return (0);
}

int	check_heredoc(t_cmd *cmd)
{
	t_redir	*tmp;
	t_doc	heredocs[100];
	char	*filename;

	tmp = cmd->infiles;
	cmd->heredoc_count = 0;
	filename = NULL;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (init_heredoc(cmd, tmp, heredocs, filename) == -1)
				return (-1);
			free(filename);
			cmd->heredoc_count++;
		}
		tmp = tmp->next;
	}
	cmd->heredocs = (t_doc *)malloc(sizeof(t_doc) * (cmd->heredoc_count + 1));
	if (!cmd->heredocs)
		ft_perror("malloc heredoc error", -1);
	memcpy(cmd->heredocs, heredocs, sizeof(t_doc) * cmd->heredoc_count);
	return (0);
}
