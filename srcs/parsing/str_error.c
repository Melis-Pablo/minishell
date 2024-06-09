/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:01 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 17:24:47 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
check_unclosed_quote:	Check if there is an unclosed quote in the string

Parameters:				char *str - the string to check

Return:					int - 1 if there is an unclosed quote, 0 otherwise

How it works:
	1. Initialize single_quotes and double_quotes to 0
	2. Loop through the string
	3. If the character is a single quote and double quotes are not open,
		toggle single_quotes
	4. If the character is a double quote and single quotes are not open,
		toggle double_quotes
	5. Return 1 if single_quotes or double_quotes are open, 0 otherwise

*/
int	check_unclosed_quote(char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (!double_quotes)
				single_quotes = !single_quotes;
		}
		else if (*str == '"')
		{
			if (!single_quotes)
				double_quotes = !double_quotes;
		}
		str++;
	}
	if (single_quotes || double_quotes)
		return (1);
	else
		return (0);
}

/*
check_backslash:	Check if the last character of the string is a backslash

Parameters:			char *str - the string to check

Return:				int - 1 if the last character is a backslash, 0 otherwise

How it works:
	1. Get the length of the string
	2. Return 1 if the last character is a backslash, 0 otherwise
*/
int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

/*
string_error:	Check if there is an unclosed quote or backslash in the string

Parameters:		char *str - the string to check

Return:			int - 1 if there is an unclosed quote or backslash, 0 otherwise

How it works:
	1. Check if there is an unclosed quote
		2. Check if there is a backslash at the end of the string
			3. Print an error message and return 1
		4. If there is an unclosed quote
			5. print an error message and return 1
	6. Return 0 if there is no unclosed quote
*/
int	string_error(char *str)
{
	if (check_unclosed_quote(str))
	{
		if (check_backslash(str))
		{
			perror("Error: Backslash not suported\n");
			return (1);
		}
		perror("Error: Unclosed quote detected\n");
		return (1);
	}
	return (0);
}
