/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:42:38 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 17:01:09 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
char	**get_flags(char **words)
{
	int count = 0;
	int i = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
			count++;
		i++;
	}

	char **flags = (char **)malloc((count + 1) * sizeof(char *));
	if (flags == NULL)
		return NULL;

	int j = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
		{
			flags[j] = words[i];
			j++;
		}
		i++;
	}
	flags[j] = NULL;

	return flags;
}

char	**get_infile(char **words)
{
	int count = 0;
	int i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], "<") == 0 || (words[i][0] == '<' && words[i][1] != '\0'))
			count++;
		i++;
	}

	char **infile = (char **)malloc((count + 1) * sizeof(char *));
	if (infile == NULL)
		return NULL;

	int j = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], "<") == 0 || (words[i][0] == '<' && words[i][1] != '\0'))
		{
			infile[j] = words[i + 1];
			j++;
		}
		i++;
	}
	infile[j] = NULL;

	return infile;
}

char	**get_outfile(char **words)
{
	int count = 0;
	int i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], ">") == 0 || (words[i][0] == '>' && words[i][1] != '\0'))
			count++;
		i++;
	}

	char **outfile = (char **)malloc((count + 1) * sizeof(char *));
	if (outfile == NULL)
		return NULL;

	int j = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], ">") == 0 || (words[i][0] == '>' && words[i][1] != '\0'))
		{
			outfile[j] = words[i + 1];
			j++;
		}
		i++;
	}
	outfile[j] = NULL;

	return outfile;
}

char	*get_delimiter(char **words)
{
	int i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], "<<") == 0 || (words[i][0] == '<' && words[i][1] == '<' && words[i][2] != '\0'))
			return words[i + 1];
		i++;
	}

	return NULL;
}

char	**get_append(char **words)
{
	int count = 0;
	int i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], ">>") == 0 || (words[i][0] == '>' && words[i][1] == '>' && words[i][2] != '\0'))
			count++;
		i++;
	}

	char **append = (char **)malloc((count + 1) * sizeof(char *));
	if (append == NULL)
		return NULL;

	int j = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (strcmp(words[i], ">>") == 0 || (words[i][0] == '>' && words[i][1] == '>' && words[i][2] != '\0'))
		{
			append[j] = words[i + 1];
			j++;
		}
		i++;
	}
	append[j] = NULL;

	return append;
}

char	**get_arguments(char **words)
{
	int count = 0;
	int i = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] != '-' && strcmp(words[i], "<") != 0 && strcmp(words[i], ">") != 0 && strcmp(words[i], "<<") != 0 && strcmp(words[i], ">>") != 0)
			count++;
		i++;
	}

	char **arguments = (char **)malloc((count + 1) * sizeof(char *));
	if (arguments == NULL)
		return NULL;

	int j = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] != '-' && strcmp(words[i], "<") != 0 && strcmp(words[i], ">") != 0 && strcmp(words[i], "<<") != 0 && strcmp(words[i], ">>") != 0)
		{
			arguments[j] = words[i];
			j++;
		}
		i++;
	}
	arguments[j] = NULL;

	return arguments;
}
*/

/*
struct s_cmd *add_tolst(struct s_cmd *head, struct s_cmd *node)
{
	if (head == NULL)
		head = node;
	else
	{
		struct s_cmd *current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
	return head;
}

struct s_cmd *cmd_builder(char **str_blocks)
{
	struct s_cmd *head = NULL;

	// Iterate through each str_block
	for (int i = 0; str_blocks[i] != NULL; i++)
	{
		// Separate str_block into words
		char **words = split_into_words(str_blocks[i]);

		// Create a new command node
		struct s_cmd *node = (struct s_cmd *)malloc(sizeof(struct s_cmd));
		node->cmd = words[0];
		node->args = get_arguments(words);
		node->flags = get_flags(words);
		node->infile = get_infile(words);
		node->outfile = get_outfile(words);
		node->delimiter = get_delimiter(words);
		node->append = get_append(words);
		node->prev = NULL;
		node->next = NULL;

		// Add the node to the command table
		head = add_tolst(head, node);
	}
	return head;
}
*/

/*
void print_cmd(struct s_cmd *cmd)
{
	printf("cmd: %s\n", cmd->cmd);
	printf("args: ");
	if (cmd->args != NULL)
	{
		for (int i = 0; cmd->args[i] != NULL; i++)
		{
			printf("%s ", cmd->args[i]);
		}
	}
	printf("\n");
	printf("flags: ");
	if (cmd->flags != NULL)
	{
		for (int i = 0; cmd->flags[i] != NULL; i++)
		{
			printf("%s ", cmd->flags[i]);
		}
	}
	printf("\n");
	printf("infile: ");
	if (cmd->infile != NULL)
	{
		for (int i = 0; cmd->infile[i] != NULL; i++)
		{
			printf("%s ", cmd->infile[i]);
		}
	}
	printf("\n");
	printf("outfile: ");
	if (cmd->outfile != NULL)
	{
		for (int i = 0; cmd->outfile[i] != NULL; i++)
		{
			printf("%s ", cmd->outfile[i]);
		}
	}
	printf("\n");
	printf("delimiter: %s\n", cmd->delimiter);
	printf("append: ");
	if (cmd->append != NULL)
	{
		for (int i = 0; cmd->append[i] != NULL; i++)
		{
			printf("%s ", cmd->append[i]);
		}
	}
	printf("\n");
	printf("---------------------\n");
}

void print_all_nodes(struct s_cmd *head)
{
	struct s_cmd *current = head;
	while (current != NULL)
	{
		print_cmd(current);
		current = current->next;
	}
}
*/
