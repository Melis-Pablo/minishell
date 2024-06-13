/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:50:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 16:26:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
is_input():	Check if the word is an input redirection.

Arguments:		char *word - the word to check.

Return:			int - 1 if the word is an input redirection, 0 otherwise.

How it works:
	1. Check if the word is "<".
	2. Check if the word starts with "<".
	3. Return 1 if the word is an input redirection, 0 otherwise.
*/
int	is_input(char *word)
{
	if (word && ft_strcmp(word, "<") == 0)
		return (1);
	if (ft_strlen(word) > 1 && word[0] == '<' )
	{
		if (word[1] == '<')
			return (0);
		return (1);
	}
	return (0);
}

/*
is_output():	Check if the word is an output redirection.

Arguments:		char *word - the word to check.

Return:			int - 1 if the word is an output redirection, 0 otherwise.

How it works:
	1. Check if the word is ">".
	2. Check if the word starts with ">".
	3. Return 1 if the word is an output redirection, 0 otherwise.
*/
int	is_output(char *word)
{
	if (word && ft_strcmp(word, ">") == 0)
		return (1);
	if (ft_strlen(word) > 1 && word[0] == '>')
	{
		if (word[1] == '>')
			return (0);
		return (1);
	}
	return (0);
}

/*
is_heredoc():	Check if the word is a heredoc redirection.

Arguments:		char *word - the word to check.

Return:			int - 1 if the word is a heredoc redirection, 0 otherwise.

How it works:
	1. Check if the word is "<<".
	2. Check if the word starts with "<<".
	3. Return 1 if the word is a heredoc redirection, 0 otherwise.
*/
int	is_heredoc(char *word)
{
	if (word && ft_strcmp(word, "<<") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '<' && word[1] == '<'))
		return (1);
	return (0);
}

/*
is_append():	Check if the word is an append redirection.

Arguments:		char *word - the word to check.

Return:			int - 1 if the word is an append redirection, 0 otherwise.

How it works:
	1. Check if the word is ">>".
	2. Check if the word starts with ">>".
	3. Return 1 if the word is an append redirection, 0 otherwise.
*/
int	is_append(char *word)
{
	if (word && ft_strcmp(word, ">>") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '>' && word[1] == '>'))
		return (1);
	return (0);
}

/*
fill_types():	Fill the types of the tokens in the lexer list.

Arguments:		t_lexer *head - the head of the lexer list.

Return:			void

How it works:
	1. Loop through the lexer list.
	2. Check if the word is an input redirection.
	3. Check if the word is an output redirection.
	4. Check if the word is a heredoc redirection.
	5. Check if the word is an append redirection.
	6. Set the type of the token.
*/
void	fill_types(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_input(tmp->word))
			tmp->type = REDIR_INPUT;
		else if (is_output(tmp->word))
			tmp->type = REDIR_OUTPUT;
		else if (is_heredoc(tmp->word))
			tmp->type = REDIR_HEREDOC;
		else if (is_append(tmp->word))
			tmp->type = REDIR_APPEND;
		else
			tmp->type = NO_REDIRECTION;
		tmp = tmp->next;
	}
}
