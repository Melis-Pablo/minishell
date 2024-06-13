/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:48:49 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 17:21:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
remove_redir_sym():	Removes redirection symbols from the tokens.

Parameters:		t_lexer *head	-	Pointer to the head of the linked list.

Return:			void

How it works:
	1. Iterates through the linked list.
	2. If the token is a redirection symbol and the word starts with the symbol,
		the symbol is removed from the word.
*/
void	remove_redir_sym(t_lexer *head)
{
	t_lexer	*tmp;
	char	*tmp_word;
	int		chars_to_remove;

	tmp = head;
	tmp_word = NULL;
	chars_to_remove = 0;
	while (tmp)
	{
		if (((tmp->type == REDIR_INPUT && tmp->word != NULL)
				|| (tmp->type == REDIR_OUTPUT && tmp->word != NULL))
			&& ((tmp->word && strncmp(tmp->word, "<", 1) == 0)
				|| (tmp->word && strncmp(tmp->word, ">", 1) == 0)))
			chars_to_remove = 1;
		else if (((tmp->type == REDIR_HEREDOC && tmp->word != NULL)
				|| (tmp->type == REDIR_APPEND && tmp->word != NULL))
			&& ((tmp->word && strncmp(tmp->word, "<<", 2) == 0)
				|| (tmp->word && strncmp(tmp->word, ">>", 2) == 0)))
			chars_to_remove = 2;
		if (chars_to_remove != 0)
		{
			tmp_word = ft_strdup(tmp->word + chars_to_remove);
			free(tmp->word);
			tmp->word = tmp_word;
		}
		tmp = tmp->next;
		chars_to_remove = 0;
	}
}

/*
add_token():	Adds a new node to the end of the linked list.

Parameters:		t_lexer *head	-	Pointer to the head of the linked list.
				t_lexer *new_node	-	Pointer to the new node to be added.

Return:			t_lexer *	-	Pointer to the head of the linked list.

How it works:
	1. If the head is NULL, the new node is the only node in the list.
	2. If the head is not NULL, the new node is added to the end of the list.
	3. The new node is added to the end of the list.
	4. The new node is returned.
*/
t_lexer	*add_token(t_lexer *head, t_lexer *new_node)
{
	t_lexer	*tmp;

	if (!head)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		return (new_node);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (head);
}

/*
take_out_node():	Removes a node from the linked list.

Parameters:		t_lexer *node	-	Pointer to the node to be removed.

Return:			t_lexer *	-	Pointer to the next node in the list.

How it works:
	1. The node is removed from the list.
	2. The next node is returned.
*/
t_lexer	*take_out_node(t_lexer *node)
{
	t_lexer	*tmp;

	tmp = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->word);
	free(node);
	return (tmp);
}

/*
remove_empty_tokens():	Removes empty tokens from the linked list.

Parameters:		t_lexer *head	-	Pointer to the head of the linked list.

Return:			void

How it works:
	1. Iterates through the linked list.
	2. If the token is empty and the next token is not NULL,
		the token is removed.
*/
void	remove_empty_tokens(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == NO_REDIRECTION && tmp->word[0] == '\0'
			&& tmp->next != NULL)
		{
			tmp = take_out_node(tmp);
		}
		tmp = tmp->next;
	}
}

/*
merge_and_clean():	Merges redirection symbols with the next token and cleans
					quotes from tokens.

Parameters:		t_lexer *head	-	Pointer to the head of the linked list.

Return:			void

How it works:
	1. Iterates through the linked list.
	2. If the token is a redirection symbol, the next token is merged with it.
		1. If the next token is a redirection symbol, the token is cleaned.
		2. If the next token is not a redirection symbol, the token is merged.
	3. If the token is not a redirection symbol, quotes are cleaned from it.
	4. The next token is checked.
	5. The process continues until the end of the list.
*/
void	merge_and_clean(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if ((tmp->type == REDIR_INPUT && ft_strcmp(tmp->word, "<") == 0)
			|| (tmp->type == REDIR_OUTPUT && ft_strcmp(tmp->word, ">") == 0)
			|| (tmp->type == REDIR_HEREDOC && ft_strcmp(tmp->word, "<<") == 0)
			|| (tmp->type == REDIR_APPEND && ft_strcmp(tmp->word, ">>") == 0))
		{
			free(tmp->word);
			if (tmp->next->type == NO_REDIRECTION)
			{
				tmp->word = ft_strdup(tmp->next->word);
				free(tmp->next->word);
				tmp->next->word = malloc(1 * sizeof(char));
				tmp->next->word[0] = '\0';
			}
			else if (tmp->next->type != NO_REDIRECTION)
			{
				tmp->word = malloc(1 * sizeof(char));
				tmp->word[0] = '\0';
			}
		}
		tmp = tmp->next;
	}
}

/*
lexer():	Converts an array of tokens into a linked list of tokens.

Parameters:		char **tokens	-	Array of tokens.

Return:			t_lexer *	-	Pointer to the head of the linked list.

How it works:
	1. Iterates through the array of tokens.
	2. Creates a new node for each token.
	3. Adds the new node to the linked list.
	4. Fills the types of the tokens.
	5. Merges redirection symbols with the next token and cleans quotes.
	6. Removes redirection symbols from the tokens.
	7. Removes empty tokens from the list.
	8. Returns the head of the linked list.
*/
t_lexer	*lexer(char **tokens)
{
	int		i;
	t_lexer	*head;
	t_lexer	*new_node;

	i = 0;
	head = NULL;
	while (tokens[i])
	{
		new_node = malloc(sizeof(t_lexer));
		if (!new_node)
			return (NULL);
		new_node->word = ft_strdup(tokens[i]);
		new_node->type = NO_REDIRECTION;
		new_node->prev = NULL;
		new_node->next = NULL;
		head = add_token(head, new_node);
		i++;
	}
	fill_types(head);
	merge_and_clean(head);
	remove_redir_sym(head);
	remove_empty_tokens(head);
	return (head);
}
