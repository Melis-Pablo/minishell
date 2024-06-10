/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/10 19:28:44 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
count_words:	count the number of words in a string

Parameters:		char *str - the string to count words in

Return:			int - the number of words in the string

How it works:	
	1. Check for string errors
	2. Skip leading spaces
	3. Loop through the string
	4. If a space is found and the next character is not a space or null,
		increment the word count
	5. Return the word count
*/
int	count_words(char *str)
{
	int	count;
	int	in_quotes;

	if (string_error(str))
		return (0);
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
get_word:	get a word from a string

Parameters:		char **str - the string to get the word from

Return:			char * - the word

How it works:	
	1. Loop through the string
	2. If a quote is found, skip to the end of the quote
	3. Allocate memory for the word
	4. Copy the word to the new string
	5. Check for invalid characters
	6. Increment the string pointer
	7. Return the word
*/
char	*get_word(char **str)
{
	char	*word;
	int		i;

	i = 0;
	while ((*str)[i] && !is_space((*str)[i]))
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '\'')
				i++;
		}
		i++;
	}
	word = ft_strndup(*str, i);
	if (check_invalid_char(word))
		return (NULL);
	*str += i;
	return (word);
}

/*
split_into_words:	split a string into words

Parameters:		char *str - the string to split

Return:			char ** - an array of words

How it works:	
	1. Skip leading spaces
	2. Count the number of words
	3. Allocate memory for the words array
	4. Loop through the string
	5. Skip leading spaces
	6. Get a word
	7. If the word is null, free the array and return null
	8. Skip leading spaces
	9. Increment the word count
	10. Return the words array
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
		if (!words[i])
		{
			free_array(words);
			return (NULL);
		}
		while (*str && is_space(*str))
			str++;
		i++;
	}
	words[word_count] = NULL;
	return (words);
}
