/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/04 14:47:29 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
check_quotes_and_pipes():	Checks if the current character is a quote or a pipe.

parameters:					char *input: The string to be checked.
							int *in_quote: Pointer to the in_quote flag.
							char *quote: Pointer to the quote character.

return value:				int: 1 if the current character is a pipe and
									not in a quote, 0 otherwise.

How it works:
	1. If the current character is a quote
		2. If in a quote and the current character is the same as the quote
			character, set in_quote to 0.
		3. If not in a quote, set the quote character to the current character
			and set in_quote to 1.
	4. If the current character is a pipe and not in a quote, return 1.
	5. Return 0.
*/
int	check_quotes_and_pipes(char *input, int *in_quote, char *quote)
{
	if (*input == '\'' || *input == '\"')
	{
		if (*in_quote && *input == *quote)
			*in_quote = 0;
		else if (!*in_quote)
		{
			*quote = *input;
			*in_quote = 1;
		}
	}
	else if (*input == '|' && !*in_quote)
		return (1);
	return (0);
}

/*
count_pipes():	Takes a string as input and returns the number of pipes.

parameters:		char *input: The string to be counted.

return value:	int count: The number of pipes.

How it works:
	1. Loop through the characters in the string.
		2. If the current character is a quote
			3. If in a quote and the current character is the same as the quote
				character, set in_quote to 0.
			4. If not in a quote, set the quote character to the current
				character and set in_quote to 1.
		5. If the current character is a pipe, increment the count.
	6. Return the count.
*/
int	count_pipes(char *input)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	while (*input)
	{
		if (check_quotes_and_pipes(input, &in_quote, &quote))
			count++;
		input++;
	}
	return (count);
}

/*
count_until_pipe():	Takes a string as input and returns the number of
					characters until the pipe.

parameters:			char *input: The string to be counted.

return value:		int count: The number of characters until the pipe.

How it works:
	1. Loop through the characters in the string.
		2. If the current character is a quote
			3. If in a quote and the current character is the same as
				the quote character, set in_quote to 0.
			4. If not in a quote, set the quote character to the
				current character and set in_quote to 1.
		5. If the current character is a pipe, break the loop.
		6. Increment the count.
	7. Return the count.
*/
int	count_until_pipe(char *input)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	while (*input)
	{
		if (check_quotes_and_pipes(input, &in_quote, &quote))
			break ;
		count++;
		input++;
	}
	return (count);
}

/*
copy_until_pipe():	Takes a string as input and returns a string.

parameters:			char *start: The string to be copied.

return value:		char *str: The copied string.

How it works:
	1. Count the number of characters until the pipe.
	2. Allocate memory for the new string.
	3. Loop through the characters until the pipe.
		4. Copy the character.
		5. Increment the index.
	6. Set the last element of the string to NULL.
	7. Return the string.
*/
char	*copy_until_pipe(char *start)
{
	int		count;
	char	*str;
	int		i;

	i = 0;
	count = count_until_pipe(start);
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < count)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
split_by_pipes():	Takes a string as input and returns an array of strings.

parameters:			char *input: The string to be split.

return value:		char **strings: An array of strings.

How it works:
	1. Count the number of pipes in the input string.
	2. Allocate memory for the array of strings.
	3. Loop through the pipes
		4. Copy the string until the pipe.
		5. Increment the index.
	6. Set the last element of the array to NULL.
	7. Return the array.
*/
char	**split_by_pipes(char *input)
{
	int		pipe_count;
	int		i;
	char	**strings;

	i = 0;
	pipe_count = count_pipes(input);
	strings = malloc((pipe_count + 2) * sizeof(char *));
	if (!strings)
		return (NULL);
	while (i <= pipe_count)
	{
		strings[i] = copy_until_pipe(input);
		input += strlen(strings[i]) + 1;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
