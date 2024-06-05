/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/05 17:43:29 by pmelis           ###   ########.fr       */
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
free_cmd_lst():	Free the linked list of commands

Parameters:		t_cmd *head - the head of the linked list

Return:			void

How it works:
	1. Loop through the linked list
	2. Free the command string
	3. Free the flags array
	4. Free the infile array
	5. Free the outfile array
	6. Free the append array
	7. Free the current node
	8. Move to the next node
	9. Free the head
*/
void	free_cmd_lst(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = head;
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
