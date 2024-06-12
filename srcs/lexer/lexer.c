/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:07:50 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/12 13:24:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
fill_types:	fills the types of the words in the list

Parameters:		t_lexer *head - the head of the list

Return:			void

How it works:
	1. Loop through the list
	2. If the word is an input redirection, set the type to REDIR_INPUT
	3. If the word is an output redirection, set the type to REDIR_OUTPUT
	4. If the word is a heredoc redirection, set the type to REDIR_HEREDOC
	5. If the word is an append redirection, set the type to REDIR_APPEND
	6. Otherwise, set the type to NO_REDIRECTION
*/
void	fill_types(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_input_redirection(tmp->word))
			tmp->type = REDIR_INPUT;
		else if (is_output_redirection(tmp->word))
			tmp->type = REDIR_OUTPUT;
		else if (is_heredoc_redirection(tmp->word))
			tmp->type = REDIR_HEREDOC;
		else if (is_append_redirection(tmp->word))
			tmp->type = REDIR_APPEND;
		else
			tmp->type = NO_REDIRECTION;
		tmp = tmp->next;
	}
}

/*
add_to_list_lexer:	adds a new node to the end of the list

Parameters:			t_lexer *head - the head of the list
					t_lexer *new_node - the new node to add

Return:				t_lexer * - the new head of the list

How it works:
	1. If the head is NULL, set the new node's next to NULL and return it
	2. Loop through the list until the last node
	3. Set the last node's next to the new node
	4. Set the new node's next to NULL
	5. Return the head
*/
t_lexer	*add_to_list_lexer(t_lexer *head, t_lexer *new_node)
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
empty_redir_words:	empties the redirection symbols from the words

Parameters:			t_lexer *head - the head of the list

Return:				void

How it works:
	1. Loop through the list
	2. If the word is a redirection symbol, free it
	3. If the word is not a redirection symbol, clean the quotes
	4. Move to the next node
*/
void	empty_redir_words(t_lexer *head)
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
				tmp->next->word = NULL;
			}
			else
				perror("Syntax error near unexpected redirection");
			break;
		}
		if (tmp->type == NO_REDIRECTION)
			tmp->word = ft_clean_quotes(tmp->word);
		tmp = tmp->next;
	}
}

void free_and_delete_empty_nodes(t_lexer *head)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;

	tmp = head;
	while (tmp)
	{
		if (tmp->word == NULL)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
}

/*
lexer:	creates a list of words and their types

Parameters:	char **words - the list of words

Return:		t_lexer * - the head of the list

How it works:
	1. Loop through the list of words
	2. Create a new node
	3. Add the new node to the list
	4. Fill the types of the words
	5. Empty the redirection symbols from the words
	6. Clean the redirection symbols
	7. Return the head of the list
*/
t_lexer	*lexer(char **words)
{
	int		i;
	t_lexer	*head;
	t_lexer	*new_node;

	i = 0;
	head = NULL;
	while (words[i])
	{
		new_node = malloc(sizeof(t_lexer));
		if (!new_node)
			return (NULL);
		new_node->word = ft_strdup(words[i]);
		new_node->type = NO_REDIRECTION;
		new_node->prev = NULL;
		head = add_to_list_lexer(head, new_node);
		i++;
	}
	fill_types(head);
	empty_redir_words(head);
	clean_redir_symbols(head);
	free_and_delete_empty_nodes(head);
	return (head);
}
