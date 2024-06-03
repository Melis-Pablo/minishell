/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 17:37:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
free_array:	free the array of strings

Parameters:	char **array - the array of strings to free

Return:		void

How it works:
	1. Loop through the array and free each string
	2. Free the array itself
*/
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
free_cmds:	free the linked list of commands

Parameters:	t_cmd *cmds - the linked list of commands to free

Return:		void

How it works:
	1. Loop through the linked list and free each command
	2. Free the linked list itself
*/
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free_array(current->flags);
		free_array(current->infile);
		free_array(current->outfile);
		free_array(current->append);
		free(current);
		current = next;
	}	
}
