/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:15:41 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/06 19:38:49 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

t_cmd	*create_node(char **words)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL; // get_cmd(words);
	new_node->args = NULL; // get_args(words);
	new_node->flags = NULL; // get_flags(words);
	new_node->infile = get_infile(words);
	new_node->outfile = NULL; // get_outfile(words);
	new_node->delimiter = NULL; // get_delimiter(words);
	new_node->append = NULL; // get_append(words);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_node_to_lst(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*current;

	current = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
		new_node->prev = current;
	}
}

t_cmd   *create_lst(char *input)
{
	t_cmd	*head;
	t_cmd	*new_node;
	char	**command_strings;
	char	**words;
	int		i;

	command_strings = split_by_pipes(input);
	head = NULL;
	i = 0;
	if (!command_strings)
		return (NULL);

	while (command_strings[i] != NULL)
	{
		words = split_into_words(command_strings[i]);
		if (!words)
			continue ;
		new_node = create_node(words);
		if (!new_node)
		{
			continue ;
		}
		add_node_to_lst(&head, new_node);
		free_array(words);
		i++;
	}
	free_array(command_strings);
	return (head);
}
