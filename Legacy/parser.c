/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/29 13:37:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///////////////////////////////////////////////////////////////////////////////
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

int	is_whitespace(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}
///////////////////////////////////////////////////////////////////////////////

char **string_blocks(char *input)
{
	int num_pipes;
	char **strings;

	num_pipes = 0;
	strings = NULL;
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

char **split_string(char *input) {
	int num_words = 0;
	char **words = NULL;
	int in_quote = 0;
	char quote = '\0';
	char *start = input;
	while (*input) {
		if (*input == '\'' || *input == '\"') {
			if (in_quote && *input == quote) {
				in_quote = 0;
				quote = '\0';
			} else if (!in_quote) {
				in_quote = 1;
				quote = *input;
			}
		} else if (!in_quote && is_whitespace(*input)) {
			if (input > start) {
				int length = input - start;
				char *word = malloc((length + 1) * sizeof(char));
				strncpy(word, start, length);
				word[length] = '\0';
				words = realloc(words, (num_words + 1) * sizeof(char *));
				words[num_words] = word;
				num_words++;
			}
			start = input + 1;
		}
		input++;
	}
	if (input > start) {
		int length = input - start;
		char *word = malloc((length + 1) * sizeof(char));
		strncpy(word, start, length);
		word[length] = '\0';
		words = realloc(words, (num_words + 1) * sizeof(char *));
		words[num_words] = word;
		num_words++;
	}
	words = realloc(words, (num_words + 1) * sizeof(char *));
	words[num_words] = NULL;
	return words;
}
