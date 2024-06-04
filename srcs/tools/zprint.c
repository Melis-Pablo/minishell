/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/04 15:20:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array:	print the array of strings

Parameters:			char **arr - the array of strings to print

Return:				void

How it works:
	1. Loop through the array and print each string
	2. Print a newline at the end
*/
void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("word %i: %s \n", i, arr[i]);
		i++;
	}
}

/*
print_cmds_list:	print the linked list of commands

Parameters:			t_cmd *head - the head of the linked list of commands

Return:				void

How it works:
	1. Loop through the linked list and print each command
	2. Print a newline at the end
*/
void	print_cmds_list(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current != NULL)
	{
		printf("--------------------\n");
		printf("cmd: %s\n", current->cmd);
		printf("args: ");
		print_str_array(current->args);
		printf("flags: ");
		print_str_array(current->flags);
		printf("infile: ");
		print_str_array(current->infile);
		printf("outfile: ");
		print_str_array(current->outfile);
		printf("delimiter: ");
		print_str_array(current->delimiter);
		printf("append: ");
		print_str_array(current->append);
		current = current->next;
	}
	printf("--------------------\n");
}
