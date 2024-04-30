/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:20:55 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/10 21:09:59 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_split():	returns an array of strings obtained by splitting ’s’ using the
				character ’c’ as a delimiter.  The array must end with a NULL
				pointer.

#Parameters:	char const *s
				char c

#Return:		char **

#How it works:	This code is an implementation of the ft_split function from
				the libft library, which splits a given string into an array
				of strings based on a delimiter character. The implementation
				uses two helper functions, st_count_words and st_handle_word,
				to count the number of words in the input string and to handle
				the creation of each word in the resulting array, respectively.

				The st_count_words function iterates through the input string
				and counts the number of words in it, using the delimiter
				character to identify the end of each word. It returns the
				total count of words.

				The st_handle_word function handles the creation of each word
				in the resulting array. It starts by skipping over any
				delimiter characters at the beginning of the word, and then
				records the starting index of the word. It then continues
				iterating through the input string until it reaches the end of
				the word, and records the ending index of the word. It then
				uses malloc to allocate enough memory for the word in the
				resulting array, copies the characters of the word into the
				allocated memory, and appends a null terminator to the end of
				the word.

				The ft_split function takes in the input string and delimiter
				character as parameters, and returns an array of strings
				representing the words in the input string. It uses the
				st_count_words helper function to determine the total number
				of words in the input string, and then uses malloc to allocate
				enough memory for an array of that size plus one additional
				element, which will be set to null to terminate the array.

				It then uses a while loop to iterate through each word in the
				input string, using the st_handle_word helper function to
				handle the creation of each word in the resulting array. If an
				error occurs during the creation of a word (such as running out
				of memory), the function calls the st_abort helper function to
				free any previously allocated memory and then returns null to
				indicate an error. Once all words have been processed, the
				function sets the last element of the resulting array to null
				to terminate it and returns the array.
*/

static size_t	st_count_words(char const *s, char separator)
{
	size_t	word_count;
	size_t	i;
	char	b_is_sep;
	char	b_was_sep;

	b_was_sep = 1;
	word_count = 0;
	i = 0;
	while (s[i])
	{
		b_is_sep = s[i] == separator;
		if (!b_is_sep && b_was_sep)
			word_count++;
		i++;
		b_was_sep = b_is_sep;
	}
	return (word_count);
}

static void	st_handle_word(char const *s, size_t *char_i,
								char separator, char **dest)
{
	size_t	word_start_idx;
	size_t	write_i;

	while (s[*char_i] == separator)
		*char_i += 1;
	word_start_idx = *char_i;
	while (s[*char_i] && s[*char_i] != separator)
		*char_i += 1;
	*dest = malloc((*char_i - word_start_idx) + 1);
	if (*dest)
	{
		write_i = 0;
		while (write_i < (*char_i - word_start_idx))
		{
			(*dest)[write_i] = s[word_start_idx + write_i];
			write_i++;
		}
		(*dest)[*char_i - word_start_idx] = '\0';
	}
}

static void	st_abort(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;
	size_t	word_count;
	size_t	word_i;
	size_t	char_i;

	if (s == NULL)
		return (NULL);
	word_count = st_count_words(s, c);
	new_array = malloc(sizeof(*new_array) * (word_count + 1));
	if (new_array == NULL)
		return (NULL);
	char_i = 0;
	word_i = 0;
	while (word_i < word_count)
	{
		st_handle_word(s, &char_i, c, &new_array[word_i]);
		if (new_array[word_i] == 0)
		{
			st_abort(new_array);
			return (0);
		}
		word_i++;
	}
	new_array[word_count] = 0;
	return (new_array);
}
