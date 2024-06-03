/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 18:01:22 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
is_space:	check if the character is a space character

Parameters:	char c - the character to check

Return:		int - 1 if the character is a space character, 0 otherwise

How it works:
	1. Check if the character is a space character
	2. Return 1 if it is, 0 otherwise
*/
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

/*
count_words:	count the number of words in the string block

Parameters:		char *str - the string to count words in

Return:			int - the number of words in the string

How it works:
	1. Initialize the count to 0
	2. Initialize the in_quotes flag to 0
	3. Skip leading spaces
	4. Loop through the string
		5. If the character is a quote, toggle the in_quotes flag
		6. If not in quotes and the character is a space
			7. If the next character is not a space or the end of the string
				8. Increment the count
		9. Move to the next character
	10. Return the count plus 1
*/
static int	count_words(char *str)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*str && is_space(*str))
		str++;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && *str == ' '
			&& *(str + 1) != ' '
			&& *(str + 1) != '\0')
			count++;
		str++;
	}
	return (count + 1);
}

/*
get_word:	get the next word from the string block

Parameters:		char **str - the pointer to the word start

Return:			char * - the word

How it works:
	1. Initialize the word_start to the pointer to the word start
	2. Initialize the in_quotes flag to 0
	3. Loop through the string
		4. If the character is a quote, toggle the in_quotes flag
		5. If not in quotes and the character is a space
			6. Break the loop
		7. Move to the next character
	8. Return the word from the word_start to the current pointer
*/
static char	*get_word(char **str)
{
	char	*word_start;
	int		in_quotes;

	word_start = *str;
	in_quotes = 0;
	while (**str && (in_quotes || **str != ' '))
	{
		if (**str == '"' || **str == '\'')
			in_quotes = !in_quotes;
		(*str)++;
	}
	return (ft_strndup(word_start, *str - word_start));
}

/*
split_into_words:	split the string into words

Parameters:			char *str - the string to split

Return:				char ** - the array of words

How it works:
	1. Initialize the word_count to the number of words in the string
	2. Allocate memory for the array of words
	3. Loop through the words
		4. Skip leading spaces
		5. Get the word
		6. Skip trailing spaces
		7. Increment the index
	8. Set the last element of the array to NULL
	9. Return the array
*/
char	**split_into_words(char *str)
{
	int		word_count;
	char	**words;
	int		i;

	i = 0;
	while (*str && is_space(*str))
		str++;
	word_count = count_words(str);
	words = malloc(sizeof(char *) * (word_count + 1));
	while (i < word_count)
	{
		while (*str && is_space(*str))
			str++;
		words[i] = get_word(&str);
		while (*str && is_space(*str))
			str++;
		i++;
	}
	words[word_count] = NULL;
	return (words);
}
