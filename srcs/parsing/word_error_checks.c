/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_error_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:51:17 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/11 14:23:17 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
check_parentheses:	Checks if a word contains a parentheses

parameters:			char *word - the word to check

return:				int - 1 if the word contains the parentheses
						0 otherwise

How it works:
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
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

/*
check_and:	Checks if a word contains an and operator

parameters:	char *word - the word to check

return:			int - 1 if the word contains the and operator
					0 otherwise

How it works:
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
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

/*
check_wildcard:	Checks if a word contains a wildcard

parameters:		char *word - the word to check

return:			int - 1 if the word contains the wildcard
					0 otherwise

How it works:
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
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

/*
check_backslash_word:	Checks if a word contains a backslash

parameters:				char *word - the word to check

return:					int - 1 if the word contains the backslash
							0 otherwise

How it works:
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
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

/*
check_semicolon:	Checks if a word contains a semicolon

parameters:			char *word - the word to check

return:				int - 1 if the word contains the semicolon
						0 otherwise

How it works:
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
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
