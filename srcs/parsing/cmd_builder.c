/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:42:38 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 18:29:45 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#get_infile():	Extracts the infile from the words array

#Parameters:	char **words - the words array

#Return value:	char ** - the infile array

#How it works:	

*/
char **get_infile(char **words) {
	int i = 0, j = 0, count = 0;
	char **outfile;

	// Count the number of outfile words
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] != '<') {
			count++;
			if (strcmp(words[i], "<") == 0 && words[i+1] != NULL) {
				i++; // Skip the next word as it's part of the outfile
			}
		}
		i++;
	}

	// Allocate memory for the outfile array
	outfile = (char **)malloc(sizeof(char *) * (count + 1));

	// Copy the outfile words into the outfile array
	i = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] != '<') {
			if (strcmp(words[i], "<") == 0 && words[i+1] != NULL) {
				outfile[j] = strdup(words[i+1]); // Copy the next word as it's part of the outfile
				i++; // Skip the next word
			} else {
				outfile[j] = strdup(words[i] + 1); // Copy the word, ignoring the '>' character
			}
			j++;
		}
		i++;
	}

	// Null terminate the outfile array
	outfile[j] = NULL;

	return outfile;
}

char **get_outfile(char **words) {
	int i = 0, j = 0, count = 0;
	char **outfile;

	// Count the number of outfile words
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] != '>') {
			count++;
			if (strcmp(words[i], ">") == 0 && words[i+1] != NULL) {
				i++; // Skip the next word as it's part of the outfile
			}
		}
		i++;
	}

	// Allocate memory for the outfile array
	outfile = (char **)malloc(sizeof(char *) * (count + 1));

	// Copy the outfile words into the outfile array
	i = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] != '>') {
			if (strcmp(words[i], ">") == 0 && words[i+1] != NULL) {
				outfile[j] = strdup(words[i+1]); // Copy the next word as it's part of the outfile
				i++; // Skip the next word
			} else {
				outfile[j] = strdup(words[i] + 1); // Copy the word, ignoring the '>' character
			}
			j++;
		}
		i++;
	}

	// Null terminate the outfile array
	outfile[j] = NULL;

	return outfile;
}

/*
#get_append():	Extracts the append from the words array

#Parameters:	char **words - the words array

#Return value:	char ** - the append array

#How it works:	
*/
char **get_append(char **words){
	int i = 0, j = 0, count = 0;
	char **append;

	// Count the number of append words
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] == '>') {
			count++;
			if (strcmp(words[i], ">>") == 0 && words[i+1] != NULL) {
				i++; // Skip the next word as it's part of the append
			}
		}
		i++;
	}

	// Allocate memory for the append array
	append = (char **)malloc(sizeof(char *) * (count + 1));

	// Copy the append words into the append array
	i = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] == '>') {
			if (strcmp(words[i], ">>") == 0 && words[i+1] != NULL) {
				append[j] = strdup(words[i+1]); // Copy the next word as it's part of the append
				i++; // Skip the next word
			} else {
				append[j] = strdup(words[i] + 2); // Copy the word, ignoring the '>>' characters
			}
			j++;
		}
		i++;
	}

	// Null terminate the append array
	append[j] = NULL;

	return append;

}

char **get_heredoc(char **words){
	int i = 0, j = 0, count = 0;
	char **append;

	// Count the number of append words
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] == '<') {
			count++;
			if (strcmp(words[i], "<<") == 0 && words[i+1] != NULL) {
				i++; // Skip the next word as it's part of the append
			}
		}
		i++;
	}

	// Allocate memory for the append array
	append = (char **)malloc(sizeof(char *) * (count + 1));

	// Copy the append words into the append array
	i = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] == '<') {
			if (strcmp(words[i], "<<") == 0 && words[i+1] != NULL) {
				append[j] = strdup(words[i+1]); // Copy the next word as it's part of the append
				i++; // Skip the next word
			} else {
				append[j] = strdup(words[i] + 2); // Copy the word, ignoring the '>>' characters
			}
			j++;
		}
		i++;
	}

	// Null terminate the append array
	append[j] = NULL;

	return append;

}

/*
#get_flags():	Extracts the flags from the words array

#Parameters:	char **words - the words array

#Return value:	char ** - the flags array

#How it works:	
	1. Count the number of flags
	2. Allocate memory for the flags array
	3. Copy the flags into the flags array
	4. Return the flags array
*/
char	**get_flags(char **words)
{
	char	**flags;
	int		i;
	int		j;
	int		count;

	i = 1; // Start from the second word
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
			count++;
		i++;
	}
	flags = (char **)malloc(sizeof(char *) * (count + 1));
	i = 1; // Start from the second word
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
		{
			flags[j] = words[i];
			j++;
		}
		i++;
	}
	flags[j] = NULL;
	return (flags);
}

// char	**get_args(char **words)
// {
// 	// iterate through the words array
// 	// if the word is not a flag, infile, outfile, append or delimiter, add it to the args array
// 	// return the args array
// }

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
	str_blocks_array = split_by_pipes(input);
	i = 0;
	while (str_blocks_array[i] != NULL)
	{
		words = split_into_words(str_blocks_array[i]);
		node = (t_cmd *)malloc(sizeof(t_cmd));
		node->cmd = words[0];
		// node->args = get_arguments(words);
		node->flags = get_flags(words);
		node->infile = get_infile(words);
		node->outfile = get_outfile(words);
		node->delimiter = get_heredoc(words);
		node->append = get_append(words);
		node->prev = NULL;
		node->next = NULL;
		head = add_to_lst(head, node);
		i++;
		free(words);
	}
	return (head);
}
