/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:55:41 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 21:31:09 by pmelis           ###   ########.fr       */
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
		free(cmd->heredocs[i].filename);
		free(cmd->heredocs[i].delimiter);
		unlink(cmd->heredocs[i].filename);
		i++;
	}
	free(cmd->heredocs);
	cmd->heredocs = NULL;
	cmd->heredoc_count = 0;
}

// t_token *create_token(const char *word, t_token_type type) {
// 	t_token *token = malloc(sizeof(t_token));
// 	token->word = strdup(word);
// 	token->type = type;
// 	token->prev = NULL;
// 	token->next = NULL;
// 	return token;
// }

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
			return -1;
		}
		if (len == 0) // EOF
			break;

		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}

		if (strcmp(line, delimiter) == 0)
		{
			break;
		}

		strcat(line, "\n");
		len++;

		if (write(tmp_fd, line, len) == -1)
		{
			perror("write");
			close(tmp_fd);
			return -1;
		}
	}

	close(tmp_fd);
	return 0;
}

int	process_all_heredocs(t_doc *heredocs, int heredoc_count)
{
	char	buffer[MAX_LINE_LEN];
	ssize_t	len;
	int		tmp_fd;
	int		i;

	i = 0;
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
				write(STDOUT_FILENO, buffer, len);
				len = read(tmp_fd, buffer, sizeof(buffer));
			}
			close(tmp_fd);
		}
		i++;
	}
	return (0);
}

int	check_heredoc(t_cmd *cmd)
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



// int main() {
// 	t_token *token_list = create_token("cat", WORD);
// 	token_list->next = create_token("<<", HEREDOC);
// 	token_list->next->prev = token_list;
// 	token_list->next->next = create_token("EOF1", WORD);
// 	token_list->next->next->prev = token_list->next;
// 	token_list->next->next->next = create_token("<<", HEREDOC);
// 	token_list->next->next->next->prev = token_list->next->next;
// 	token_list->next->next->next->next = create_token("EOF2", WORD);
// 	token_list->next->next->next->next->prev = token_list->next->next->next;

// 	 t_cmd *cmd;






// 	if (check_heredoc(cmd) != 0) {
// 		fprintf(stderr, "Failed to handle heredocs\n");     //->putstrfd()
	
// 		return 1;
// 	}





// 	if (process_all_heredocs(cmd->heredocs, cmd->heredoc_count) != 0)
// 	{
// 	fprintf(stderr, "Failed to process heredocs\n");        //->putstrfd()
// 	cleanup_heredocs(&cmd);
// 	return (1);
// 	}

	
// 	cleanup_heredocs(&cmd);
// 	// Free token list
// 	return 0;
// }


/*
int	check_heredoc(t_cmd *cmd)
{
	t_token *current = token_list;
	t_doc heredocs[MAX_HEREDOCS];
	int heredoc_count = 0;
	char filename[20];

	while (current != NULL)
	{
		if (current->type == HEREDOC && current->next != NULL)
		{
			if (heredoc_count >= MAX_HEREDOCS)
			{
				fprintf(stderr, "Too many heredocs\n");         //->putstrfd()
				return -1;
			}
			//snprintf(filename, sizeof(filename), "/tmp/heredoc_%d", heredoc_count);
			heredocs[heredoc_count].filename = strdup(filename);
			heredocs[heredoc_count].delimiter = strdup(current->next->word);

			free(current->word);
			current->word = strdup(filename);
			current->type = INPUT;

			// Remove the delimiter token
			t_token *temp = current->next;
			current->next = temp->next;
			if (temp->next)
				temp->next->prev = current;
			free(temp->word);
			free(temp);
			heredoc_count++;
		}
		current = current->next;
	}

	cmd->heredocs = (t_doc *)malloc(sizeof(t_doc) * heredoc_count);
	if (cmd->heredocs == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for heredocs\n");        //->putstrfd()
		return -1;
	}
	memcpy(cmd->heredocs, heredocs, sizeof(t_doc) * heredoc_count);
	cmd->heredoc_count = heredoc_count;
	return (0);
}
*/