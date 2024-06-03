/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:42:38 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 12:15:39 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
add_to_lst():	Adds a node to the end of the list

Parameters:		t_cmd *head - the head of the list
				t_cmd *node - the node to be added

Return value:	t_cmd * - the head of the list

How it works:	
	1. If the list is empty, the head is set to the node
	2. Otherwise, the node is added to the end of the list
	3. The head of the list is returned
*/
t_cmd	*add_to_lst(t_cmd *head, t_cmd *node)
{
	t_cmd	*current;

	if (head == NULL)
		head = node;
	else
	{
		current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
	return (head);
}

/*
#build_cmd_list():	Buils a list of commands from the input string

#Parameters:		char *input - the input string

#Return value:		struct s_cmd * - the head of the list of commands

#How it works:		
	1. Split the input string into blocks
	2. For each block, split it into words
	3. Create a new command node
	4. Add the node to the command table
	5. Return the head of the list
*/
t_cmd	*cmd_builder(char *input)
{
	t_cmd	*head;
	char	**str_blocks_array;
	char	**words;
	t_cmd	*node;
	int		i;

	head = NULL;
	str_blocks_array = str_blocks(input);
	i = 0;
	while (str_blocks_array[i] != NULL)
	{
		words = split_into_words(str_blocks_array[i]);
		node = (t_cmd *)malloc(sizeof(t_cmd));
		node->cmd = words[0];
		// node->args = get_arguments(words);
		// node->flags = get_flags(words);
		// node->infile = get_infile(words);
		// node->outfile = get_outfile(words);
		// node->delimiter = get_delimiter(words);
		// node->append = get_append(words);
		node->prev = NULL;
		node->next = NULL;
		head = add_to_lst(head, node);
		i++;
		free(words);
	}
	return (head);
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
		printf("cmd: %s\n", current->cmd);
		// printf("args: ");
		// print_str_array(current->args);
		// printf("flags: ");
		// print_str_array(current->flags);
		// printf("infile: ");
		// print_str_array(current->infile);
		// printf("outfile: ");
		// print_str_array(current->outfile);
		// printf("delimiter: %s\n", current->delimiter);
		// printf("append: ");
		// print_str_array(current->append);
		current = current->next;
	}
}
