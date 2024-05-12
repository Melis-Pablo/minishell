/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:56:55 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/12 17:54:11 by pmelis           ###   ########.fr       */
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
					7. Set next
					8. Set prev
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

t_lexer	*lexer(char *input)
{
	t_lexer	*head = NULL;
	t_lexer	*current = NULL;
	char	*token = NULL;
	t_token_type token_type = NONE;
	int		index = 0;

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
