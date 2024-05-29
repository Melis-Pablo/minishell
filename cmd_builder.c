/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:42:38 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/29 23:28:06 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_flags(char **words)
{
	// Iterate through words
	// If word starts with '-' and is not a command, it is a flag
	// Add it to the flags array
	// Return the flags array
}

char	**get_infile(char **words)
{
	// Iterate through words
	// If word is '<', the next word is the infile. or if word starts with only one '<', the rest of the word is the infile
	// add it to the infile array
	// Return the infile array
}

char	**get_outfile(char **words)
{
	// Iterate through words
	// If word is '>', the next word is the outfile. or if word starts with only one '>', the rest of the word is the outfile
	// add it to the outfile array
	// Return the outfile array
}

char	*get_delimiter(char **words)
{
	// Iterate through words
	// If word is '<<', the next word is the delimiter. or if word starts with only one '<<', the rest of the word is the delimiter
	// return the delimiter
}

char	**get_append(char **words)
{
	// Iterate through words
	// If word is '>>', the next word is the append. or if word starts with only one '>>', the rest of the word is the append
	// add it to the append array
	// Return the append array
}

char	**get_arguments(char **words)
{
	// Iterate through words
	// If word is not a flag, infile, outfile, delimiter or append, it is an argument
	// Add it to the arguments array
	// Return the arguments array
}

struct s_cmd *add_tolst(struct s_cmd *head, struct s_cmd *node)
{
	if (head == NULL)
	{
		head = node;
	}
	else
	{
		struct s_cmd *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
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
