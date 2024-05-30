/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/30 16:29:36 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static int count_words(char *str_block)
{
    int count = 0;
    int in_quotes = 0;

    while (*str_block && is_space(*str_block))
        str_block++;
    while (*str_block)
	{
        if (*str_block == '"' || *str_block == '\'')
            in_quotes = !in_quotes;
        if (!in_quotes && *str_block == ' ' && *(str_block + 1) != ' ' && *(str_block + 1) != '\0')
            count++;
        str_block++;
    }
    printf("Word Count: %d\n", count);
    return count + 1;
}

static char *get_word(char **str_block)
{
	char *word_start;
	int in_quotes;

	word_start = *str_block;
	in_quotes = 0;
	while (**str_block && (in_quotes || **str_block != ' '))
	{
		if (**str_block == '"' || **str_block == '\'')
			in_quotes = !in_quotes;
		(*str_block)++;
	}
	return strndup(word_start, *str_block - word_start);
}

char **split_into_words(char *str_block)
{
	int word_count;
	char **words;
	int i;

	while (*str_block && is_space(*str_block))
		str_block++;
	word_count = count_words(str_block);
	words = malloc(sizeof(char *) * (word_count + 1));
	i = 0;
	while (i < word_count)
	{
		while (*str_block && is_space(*str_block))
			str_block++;
		words[i] = get_word(&str_block);
		while (*str_block && is_space(*str_block))
			str_block++;
		i++;
	}
	words[word_count] = NULL;
	return words;
}

void print_all(char **strings)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	while (strings[i] != NULL) {
		printf("String: >%s<\n", strings[i]);
		words = split_into_words(strings[i]);
		j = 0;
		while (words[j] != NULL)
		{
			printf("Word %d: >%s<\n", j+1, words[j]);
			j++;
		}
		i++;
	}
}
