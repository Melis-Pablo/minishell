/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/11 17:49:45 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
add_node_to_list:	adds a new node to the end of the list

Parameters:			t_cmd *head - the head of the list
					t_cmd *new_cmd - the new node to add

Return:				t_cmd * - the new head of the list

How it works:
	1. If the head is NULL, set the new node's next to NULL and return it
	2. Loop through the list until the last node
	3. Set the last node's next to the new node
	4. Set the new node's next to NULL
	5. Return the head
*/
t_cmd	*add_node_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!*head)
	{
		new_cmd->next = NULL;
		return (new_cmd);
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	new_cmd->next = NULL;
	return (*head);
}

/*
build_node:	builds a new node from a list of words

Parameters:		char **words - the list of words

Return:			t_cmd * - the new node

How it works:
	1. Create a new node
	2. Lex the list of words
	3. If the lexing failed, return NULL
	4. Set the new node's lexer to the lexed list
	5. Return the new node
*/
t_cmd	*build_node(char **words)
{
	t_lexer	*lexed_list;
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	lexed_list = lexer(words);
	if (!lexed_list)
		return (NULL);
	new_cmd->lexer = lexed_list;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*
process_words:	processes a list of words

Parameters:		char **words - the list of words
				t_cmd *head - the head of the list

Return:			t_cmd * - the new head of the list

How it works:
	1. Build a new node from the list of words
	2. If the building failed, return NULL
	3. Add the new node to the list
	4. Return the new head
*/
t_cmd	*process_words(char **words, t_cmd *head)
{
	t_cmd	*new_cmd;

	new_cmd = build_node(words);
	if (!new_cmd)
	{
		free_array(words);
		free_cmd_lst(head);
		return (NULL);
	}
	head = add_node_to_list(&head, new_cmd);
	return (head);
}

/*
process_string:	processes a string

Parameters:		char *str - the string
				t_cmd *head - the head of the list

Return:			t_cmd * - the new head of the list

How it works:
	1. Split the string into words
	2. If the splitting failed, return NULL
	3. Process the list of words
	4. Free the array of words
	5. If the processing failed, return NULL
	6. Return the new head
*/
t_cmd	*process_string(char *str, t_cmd *head)
{
	char	**words;

	words = split_into_words(str);
	if (!words)
		return (NULL);
	head = process_words(words, head);
	free_array(words);
	if (!head)
		return (NULL);
	return (head);
}

/*
build_struct:	builds a struct from an input string

Parameters:		char *input - the input string

Return:			t_cmd * - the head of the list

How it works:
	1. Split the input string by pipes
	2. If the splitting failed, return NULL
	3. Loop through the list of strings
	4. Process each string
	5. If the processing failed, free the array of strings and return NULL
	6. Free the array of strings
	7. Return the head
*/
t_cmd	*build_struct(char *input)
{
	char	**strings;
	int		i;
	t_cmd	*head;

	head = NULL;
	strings = split_by_pipes(input);
	i = 0;
	while (strings[i] != NULL)
	{
		head = process_string(strings[i], head);
		if (!head)
		{
			free_array(strings);
			return (NULL);
		}
		i++;
	}
	free_array(strings);
	return (head);
}
