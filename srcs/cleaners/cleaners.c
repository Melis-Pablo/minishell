/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:11:17 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 14:41:12 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
free_array():	Free the array of strings.

Arguments:		char **arr - the array of strings.

Return:			void

How it works:
	1. Loop through the array and free each string.
	2. Free the array.
*/
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
free_lexer_list():	Free the linked list of t_lexer.

Arguments:		t_lexer *head - the head of the linked list.

Return:			void

How it works:
	1. Loop through the linked list and free each node.
	2. Free the linked list.
*/
void	free_lexer_list(t_lexer *head)
{
	t_lexer	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
}

/*
free_cmd_lst():	Free the linked list of t_cmd.

Arguments:		t_cmd *cmds - the head of the linked list.

Return:			void

How it works:
	1. Loop through the linked list and free each node.
	2. Free the linked list.
*/
void	free_cmd_lst(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_lexer_list(tmp->lexer);
		free(tmp);
	}
}
