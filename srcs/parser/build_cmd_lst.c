/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:53:44 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:26:35 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
