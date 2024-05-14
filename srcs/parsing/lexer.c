/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:56:55 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/14 15:57:00 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#new_lexer_node():	Creates a new token node

#Parameters:		char *str
					t_token_type token
					int index

#Return value:		t_lexer	*node

#How it works:		1. Declares node var
					2. Assigns memory
					3. Memory allocation fail check
						4. return null if failed
					5. Set str
					6. Set Token
					7. Set next to NULL
					8. Set prev to NULL
					9. Set Index
					10. return Node
*/
t_lexer	*new_lexer_node(char *str, t_token_type token, int index)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = token;
	node->next = NULL;
	node->prev = NULL;
	node->index = index;
	return (node);
}

/*
#create_token():	creates/determines node

#Parameters:		char **input
					char **token
					t_token_type *token_type

#Return value:		void

#How it works:		1.
					2.
					3.
					4.
					5.
					6.
					7.
					8.
					9.
					10.
*/
void	create_token(char **input, char **token, t_token_type *token_type)
{
	char	*start;
	char	quote;

	if (**input == '|')
	{
		*token = NULL;
		*token_type = PIPE;
		(*input)++;
	}
	else
	{
		start = *input;
		while (**input && **input != '|')
		{
			if (**input == '\'' || **input == '\"')
			{
				quote = *(*input)++;
				while (**input && **input != quote)
					(*input)++;
				if (**input)
					(*input)++;
			}
			else
				(*input)++;
		}
		*token = strndup(start, *input - start);
		*token_type = NONE;
	}
}

/*
#lexer():		Separates the input str into a linked list of nodes which
				are either pipes or str lines

#Parameters:	char *input

#Return value:	t_lexer *head

#How it works:	1. Declare t_lexer *head
				2. Declare t_lexer *current
				3. Declare char *token
				4. Declare t_token_type = NONE
				5. Declare index = 0
				6. set head to null
				7. set current to null
				8. set token  to null
				9. set token_type to NONE
				10. set index to 0
				11. while *str still going
					a. create token
					b. if there is no head yet
						1. head = new node
						2. current = head
					c. else (from 2nd node forward)
						1. current->next = new node
						2. current->next->prev = current
						3. current = current->next
					d. increase index
				12. return(head node)
*/
t_lexer	*lexer(char *input)
{
	t_lexer			*head;
	t_lexer			*current;
	char			*token;
	t_token_type	token_type;
	int				index;

	head = NULL;
	current = NULL;
	token = NULL;
	token_type = NONE;
	index = 0;
	while (*input)
	{
		create_token(&input, &token, &token_type);
		if (!head)
		{
			head = new_lexer_node(token, token_type, index);
			current = head;
		}
		else
		{
			current->next = new_lexer_node(token, token_type, index);
			current->next->prev = current;
			current = current->next;
		}
		index++;
	}
	return (head);
}
