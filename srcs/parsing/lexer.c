/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:56:55 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/14 16:36:19 by pmelis           ###   ########.fr       */
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
#create_token():	Creates a token from the input string

#Parameters:		char **input
                    char **token
                    t_token_type *token_type

#Return value:		void

#How it works:		
1. Declare char *start: This will hold the starting position of the token
						in the input string.
2. Declare char quote: This will hold the type of quote character if one is
						encountered in the input string.
3. If **input equals '|':
    a. *token is set to NULL: This indicates that the token is a pipe character.
    b. *token_type is set to PIPE: This sets the type of the token to PIPE.
    c. *input is incremented: This moves the input pointer to the next character.
4. Else (**input is not a pipe):
    a. start is set to *input: This sets the start of the token to the current
		position in the input string.
    b. While **input is not NULL and not a pipe:
        1. If **input equals '\'' or '\"':
            a. quote is set to the current character in the input string
				and the input pointer is incremented.
            b. The input pointer is incremented until a matching quote is found
				or the end of the string is reached.
            c. If a matching quote is found, the input pointer is incremented
				again to move past the quote.
        2. If **input is not a quote, the input pointer is incremented.
    c. *token is set to a new string that contains the characters from start to
		the current position in the input string.
    d. *token_type is set to NONE: This indicates that the token is not a
		special character.
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
