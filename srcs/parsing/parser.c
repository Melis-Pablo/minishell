/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/27 17:26:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
