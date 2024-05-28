/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/28 17:31:46 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
#count_chars_until_pipe():	count chars until |

#Parameters:				char *input

#Return value:				int count

#How it works:				
	1. Initialize count to 0, quote to '\0' and in_quote to 0
	2. Loop through the input string
	3. If the current character is a quote, check if it is the same as the previous quote
	4. If it is, set in_quote to 0
	5. If it is not, set in_quote to 1 and quote to the current character
	6. If the current character is a pipe and not in a quote, break the loop
	7. Increment count and input
	8. Return count
*/
int	count_chars_until_pipe(char *input)
{
	int		count;
	char	quote;
	int		in_quote;

	count = 0;
	quote = '\0';
	in_quote = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (in_quote && *input == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = *input;
				in_quote = 1;
			}
		}
		else if (*input == '|' && !in_quote)
			break ;
		count++;
		input++;
	}
	return (count);
}

/*
#add_string():	adds a string to a string array

#Parameters:	char **strings, char *str, int num_pipes

#Return value:	char **new_strings

#How it works:	
	1. Initialize i to 0
	2. Allocate memory for a new string array
	3. Loop through the strings array
	4. Copy the strings to the new_strings array
	5. Free the strings array
	6. Add the new string to the new_strings array
	7. Return new_strings
*/
char **add_string(char **strings, char *str, int num_pipes)
{
	char **new_strings;
	int i;

	i = 0;
	new_strings = malloc((num_pipes + 1) * sizeof(char *));
	while (i < num_pipes)
	{
		new_strings[i] = strings[i];
		i++;
	}
	free(strings);
	new_strings[num_pipes] = str;
	return (new_strings);
}

int count_pipes(char *input)
{
	int count;
	char quote;
	int in_quote;

	count = 0;
	quote = '\0';
	in_quote = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (in_quote && *input == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = *input;
				in_quote = 1;
			}
		}
		else if (*input == '|' && !in_quote)
			count++;
		input++;
	}
	return (count);
}

char	**string_blocks(char *input)
{
	char	**blocks;
	int		num_pipes;
	int		count;

	num_pipes = count_pipes(input);
	count = 0;
	blocks = malloc(num_pipes * sizeof(char *));
}
