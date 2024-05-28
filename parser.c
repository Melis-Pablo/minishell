/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/28 16:03:34 by pmelis           ###   ########.fr       */
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

char	**string_blocks(char *input)
{
	int		num_pipes;
	char	**strings;
	int		count;
	char	*str;

	num_pipes = 0;
	strings = NULL;
	while (*input)
	{
		count = count_chars_until_pipe(input);
		str = malloc((count + 1) * sizeof(char));
		strncpy(str, input, count);
		str[count] = '\0';
		strings = realloc(strings, (num_pipes + 1) * sizeof(char *));
		strings[num_pipes] = str;
		num_pipes++;
		input += count;
		if (*input == '|')
			input++;
	}
	return (strings);
}
