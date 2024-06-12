/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:24:03 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/12 17:32:24 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ADD ERROR HANDLING FOR <<<, ><<, >><<, etc and checks for <file<file, etc
void	clean_redir_symbols(t_lexer *head)
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
is_input_redirection:	checks if a word is an input redirection

Parameters:				char *word - the word to check

Return:					int - 1 if the word is an input redirection, 0 otherwise

How it works:
	1. If the word is "<", return 1
	2. If the word is longer than 1 character and the first character is "<"
	3. If the second character is not "<", return 1
	4. Return 0
*/
int	is_input_redirection(char *word)
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
is_output_redirection:	checks if a word is an output redirection

Parameters:				char *word - the word to check

Return:					int - 1 if the word is an output redirection, 0 otherwise

How it works:
	1. If the word is ">", return 1
	2. If the word is longer than 1 character and the first character is ">"
	3. If the second character is not ">", return 1
	4. Return 0
*/
int	is_output_redirection(char *word)
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
is_heredoc_redirection:	checks if a word is a heredoc redirection

Parameters:				char *word - the word to check

Return:					int - 1 if the word is a heredoc redirection, 0 otherwise

How it works:
	1. If the word is "<<", return 1
	2. If the word is longer than 2 characters
		and the first two characters are "<<"
	3. Return 1
	4. Return 0
*/
int	is_heredoc_redirection(char *word)
{
	if (word && ft_strcmp(word, "<<") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '<' && word[1] == '<'))
		return (1);
	return (0);
}

/*
is_append_redirection:	checks if a word is an append redirection

Parameters:				char *word - the word to check

Return:					int - 1 if the word is an append redirection, 0 otherwise

How it works:
	1. If the word is ">>", return 1
	2. If the word is longer than 2 characters
		and the first two characters are ">>"
	3. Return 1
	4. Return 0
*/
int	is_append_redirection(char *word)
{
	if (word && ft_strcmp(word, ">>") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '>' && word[1] == '>'))
		return (1);
	return (0);
}
