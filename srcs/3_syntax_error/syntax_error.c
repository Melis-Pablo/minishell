/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:38:02 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:23:21 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ck_in_ch(char *word, char c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(word);
	i = 0;
	while (i < len)
	{
		if (word[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_quoted(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (len > 0)
	{
		if ((word[0] == '\'' || word[0] == '\"') && word[0] == word[len - 1])
			return (1);
	}
	return (0);
}

int	check_errors(char *word)
{
	int	i;

	i = 0;
	if (is_quoted(word))
		return (0);
	if (ck_in_ch(word, ';'))
		i = 1;
	if (ck_in_ch(word, '&'))
		i = 2;
	if (ck_in_ch(word, '|'))
		i = 3;
	if (ck_in_ch(word, '(') || ck_in_ch(word, ')'))
		i = 4;
	if (ck_in_ch(word, '*'))
		i = 5;
	if (ck_in_ch(word, '\\'))
		i = 6;
	if (ck_in_ch(word, '>') || ck_in_ch(word, '<'))
		i = 7;
	if (unclosed_quotes(word))
		i = 8;
	return (i);
}

int	syntax_error(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (check_errors(tmp->word))
			{
				printf("parse error near token: %s\n", tmp->word);
				return (1);
			}
		}
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			if (tmp->word == NULL)
			{
				printf("parse error near token: %s\n", tmp->prev->word);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
