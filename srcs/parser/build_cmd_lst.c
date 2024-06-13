/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:53:44 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 18:02:16 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
add_node_to_list():	Adds a new node to the end of the linked list.

Parameters:		t_cmd **head	-	Pointer to the head of the linked list.
				t_cmd *new_cmd	-	Pointer to the new node.

Return:			t_cmd *		-	Pointer to the head of the linked list.

How it works:
	1. If the list is empty, the new node is the head.
	2. Otherwise, the new node is added to the end of the list.
*/
t_cmd	*add_node_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!*head)
	{
		new_cmd->next = NULL;
		return (new_cmd);
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	new_cmd->next = NULL;
	return (*head);
}

/*
build_node():	Builds a new node for the linked list.

Parameters:		char **tokens	-	Array of tokens.

Return:			t_cmd *		-	Pointer to the new node.

How it works:
	1. Allocates memory for the new node.
	2. Calls the lexer function to create a linked list of tokens.
	3. If the lexer function returns NULL, the function returns NULL.
	4. Assigns the linked list to the new node.
	5. Assigns NULL to the next pointer of the new node.
	6. Returns the new node.
*/
t_cmd	*build_node(char **tokens)
{
	t_lexer	*lexed_list;
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	lexed_list = lexer(tokens);
	if (!lexed_list)
		return (NULL);
	new_cmd->lexer = lexed_list;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*
process_tokens():	Processes the tokens and adds them to the linked list.

Parameters:		char **tokens	-	Array of tokens.
				t_cmd *head	-	Pointer to the head of the linked list.

Return:			t_cmd *		-	Pointer to the head of the linked list.

How it works:
	1. Calls the build_node function to create a new node.
	2. If the build_node function returns NULL,
		the function frees the tokens array, frees the linked list,
		and returns NULL.
	3. Adds the new node to the linked list.
	4. Returns the head of the linked list.
*/
t_cmd	*process_tokens(char **tokens, t_cmd *head)
{
	t_cmd	*new_cmd;

	new_cmd = build_node(tokens);
	if (!new_cmd)
	{
		free_array(tokens);
		free_cmd_lst(head);
		return (NULL);
	}
	head = add_node_to_list(&head, new_cmd);
	return (head);
}

/*
process_pipes():	Processes the pipes and adds them to the linked list.

Parameters:		char *pipe	-	Pipe string.
				t_cmd *head	-	Pointer to the head of the linked list.

Return:			t_cmd *		-	Pointer to the head of the linked list.

How it works:
	1. Splits the pipe string into an array of tokens.
	2. If the array of tokens is NULL, the function returns NULL.
	3. Calls the process_tokens function to add the tokens to the linked list.
	4. Frees the array of tokens.
	5. If the process_tokens function returns NULL, the function returns NULL.
	6. Returns the head of the linked list.
*/
t_cmd	*process_pipes(char *pipe, t_cmd *head)
{
	char	**tokens;

	tokens = split_tokens(pipe);
	if (!tokens)
		return (NULL);
	head = process_tokens(tokens, head);
	free_array(tokens);
	if (!head)
		return (NULL);
	return (head);
}

/*
build_cmds():	Builds the linked list of commands.

Parameters:		char *input	-	Input string.

Return:			t_cmd *		-	Pointer to the head of the linked list.

How it works:
	1. Splits the input string into an array of pipes.
	2. If the array of pipes is NULL, the function returns NULL.
	3. Iterates through the array of pipes and calls the process_pipes function.
	4. If the process_pipes function returns NULL, the function frees the array
		and returns NULL.
	5. Frees the array of pipes.
	6. Returns the head of the linked list.
*/
t_cmd	*build_cmds(char *input)
{
	char	**pipes;
	int		i;
	t_cmd	*head;

	head = NULL;
	pipes = split_pipeline(input);
	i = 0;
	while (pipes[i] != NULL)
	{
		head = process_pipes(pipes[i], head);
		if (!head)
		{
			free_array(pipes);
			return (NULL);
		}
		i++;
	}
	free_array(pipes);
	return (head);
}
