/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/05 17:53:58 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
is_space():	Checks if the character is a space

Parameters:	char c - the character to check

Return:		int - 1 if the character is a space, 0 otherwise

How it works:
	1. Check if the character is a space
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
count_words():	Counts the number of words in the string

Parameters:		char *str - the string to count words in

Return:			int - the number of words

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
	10. Return the count + 1
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
get_word():	Extracts a word from the string

Parameters:	char **str - the address of the string to extract the word from

Return:			char * - the extracted word

How it works:
	1. Initialize the word_start to the address of the string
	2. Initialize the in_quotes flag to 0
	3. Loop through the string
		4. If the character is a quote, toggle the in_quotes flag
		5. If not in quotes and the character is a space
			6. Break the loop
		7. Move to the next character
	8. Return a copy of the word
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
split_into_words():	Splits the string into words

Parameters:			char *str - the string to split

Return:				char ** - the array of words

How it works:
	1. Skip leading spaces
	2. Count the number of words
	3. Allocate memory for the array of words
	4. Loop through the words
		5. Skip leading spaces
		6. Extract the word
		7. Skip trailing spaces
	8. Return the array of words

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
