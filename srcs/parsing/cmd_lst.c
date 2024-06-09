/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 19:27:43 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd(char **words)
{
	//first non redirection word
	//clean_quotes() function should be used to remove quotes from the command name
}

char	**get_args(char **words)
{
	//all non redirection words after the command word that are not flags
	//clean_quotes() function should be used to remove quotes from the arguments
}

char	**get_flags(char **words)
{
	//all non redirection words starting with '-' after the command word
	//clean_quotes() function should be used to remove quotes from the flags
}

/*
redirections are: words starting with '<', '>', '<<', '>>' characters. 
	They are followed by a file name. If there is no file name,
	the next word is the file name.
	
	<	should redirect input.
	>	should redirect output.
	<<	should be given a delimiter
	>>	should redirect output in append mode.
*/
t_redirection	*get_redirs(char **words)
{
	//all redirection words
	//return a linked list of redirections
	//each node contains a redirection type and a file name
	//before setting the file name, clean_quotes() function should be used to remove quotes
	//the last node points to NULL
	//the first node is returned
	//if there are no redirections, return NULL
}

/*
build_node():	creates a new t_cmd node and fills it with the data from the
				words array. It returns a pointer to the new node.

parameters:		char **words - an array of strings containing the command name,
				arguments, flags, and redirections.

returns:		t_cmd *node - a pointer to the new node.

How it works:	
*/
t_cmd	*build_node(char **words)
{
	// fill command name
	// fill arguments
	// fill flags
	// fill redirections
	// return the new node
}

t_cmd	*add_node_to_list(t_cmd *head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!head)
		return (new_cmd);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	new_cmd->prev = tmp;
	return (head);
}

t_cmd	*build_cmd_lst(char *input)
{
	char	**strings;
	char	**words;
	int		i;
	t_cmd	*head;
	t_cmd	*new_cmd;

	head = NULL;
	new_cmd = NULL;
	strings = split_by_pipes(input);
	i = 0;
	while (strings[i] != NULL)
	{
		words = split_into_words(strings[i]);
		if (!words)
		{
			free_array(strings);
			return (NULL);
		}
		new_cmd = build_node(words);
		head = add_node_to_list(head, new_cmd);
		free_array(words);
		i++;
	}
	free_array(strings);
	return (head);
}
