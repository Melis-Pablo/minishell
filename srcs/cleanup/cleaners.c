/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/11 17:51:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
free_array():	Free the array of strings

Parameters:		char **arr - the array of strings to free

Return:			void

How it works:
	1. Loop through the array of strings
	2. Free each string
	3. Free the array
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
free_cmd_lst():	Free the list of commands

Parameters:		t_cmd *cmds - the head of the list of commands to free

Return:			void

How it works:
	1. Loop through the list of commands
	2. Free the list of lexers
	3. Free the command
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

/*
free_lexer_list():	Free the list of lexers

Parameters:			t_lexer *head - the head of the list of lexers to free

Return:				void

How it works:
	1. Loop through the list of lexers
	2. Free the word
	3. Free the lexer
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
