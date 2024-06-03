/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 13:32:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#print_all():	prints all strings and words in a 2D array of strings

#Parameters:	char **strings

#Return value:	void

#How it works:	
	1. Initialize i to 0
	2. While strings[i] is not NULL
		1. Print the string
		2. Split the string into words
		3. Initialize j to 0
		4. While words[j] is not NULL
			1. Print the word
			2. Increment j
		5. Increment i
*/
void	print_all(char **strings)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	while (strings[i])
	{
		printf("String: >%s<\n", strings[i]);
		words = split_into_words(strings[i]);
		j = 0;
		while (words[j])
		{
			printf("Word %d: >%s<\n", j + 1, words[j]);
			j++;
		}
		i++;
		clean_blocks(words);
	}
}

void	print_str_array(char **arr)	
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s ", arr[i]);
		i++;
	}
	printf("\n");
}

/*
#print_cmds_list():	Prints the list of commands 

#Parameters:		t_cmd *head - the head of the list

#Return value:		void

#How it works:		
	1. While the list is not empty, print the command
*/
void	print_cmds_list(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current != NULL)
	{
		printf("--------------------\n");
		printf("cmd: %s\n", current->cmd);
		// printf("args: ");
		// print_str_array(current->args);
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
