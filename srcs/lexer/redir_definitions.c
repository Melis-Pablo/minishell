/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_definitions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:50:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:30:50 by pmelis           ###   ########.fr       */
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

int	is_heredoc_redirection(char *word)
{
	if (word && ft_strcmp(word, "<<") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '<' && word[1] == '<'))
		return (1);
	return (0);
}

int	is_append_redirection(char *word)
{
	if (word && ft_strcmp(word, ">>") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '>' && word[1] == '>'))
		return (1);
	return (0);
}
