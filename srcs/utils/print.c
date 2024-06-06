/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/06 19:07:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array():	Prints an array of strings

Parameters:			char **arr - the array of strings to print

Return:				void

How it works:
	1. Loop through the array of strings
	2. Print each string
*/
void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s, ", arr[i]);
		i++;
	}
	printf("\n");
}

/*
print_cmds_list():	Prints the linked list of commands

Parameters:			t_cmd *head - the head of the linked list

Return:				void

How it works:
	1. Loop through the linked list
	2. Print the command string
	3. Print the flags array
	4. Print the infile array
	5. Print the outfile array
	6. Print the append array
	7. Move to the next node
*/
void	print_cmds_list(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current != NULL)
	{
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
		printf("--------------------\n");
	}
}
