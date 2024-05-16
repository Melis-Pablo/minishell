/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/16 14:54:43 by pmelis           ###   ########.fr       */
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

char **new_lexer(char *input)
{
	int num_pipes = 0;
	char **strings = NULL;
	while (*input)
	{
		int count = count_chars_until_pipe(input);
		char *str = malloc((count + 1) * sizeof(char));
		strncpy(str, input, count);
		str[count] = '\0';
		strings = realloc(strings, (num_pipes + 1) * sizeof(char *));
		strings[num_pipes] = str;
		num_pipes++;
		input += count;
		if (*input == '|')
			input++;
	}
	return strings;
}
