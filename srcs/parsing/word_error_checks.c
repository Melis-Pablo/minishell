/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_error_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:51:17 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 18:00:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_parentheses(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (ft_strcmp(word, "()") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '(')
			return (1);
		if (word[len - 1] == ')')
			return (1);
	}
	return (0);
}

int	check_and(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (ft_strcmp(word, "&&") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '&')
			return (1);
		if (word[len - 1] == '&')
			return (1);
	}
	return (0);
}

int	check_wildcard(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (ft_strcmp(word, "*") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '*')
			return (1);
		if (word[len - 1] == '*')
			return (1);
	}
	return (0);
}

int	check_backslash_word(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (ft_strcmp(word, "\\") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '\\')
			return (1);
		if (word[len - 1] == '\\')
			return (1);
	}
	return (0);
}

int	check_semicolon(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (ft_strcmp(word, ";") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == ';')
			return (1);
		if (word[len - 1] == ';')
			return (1);
	}
	return (0);
}
