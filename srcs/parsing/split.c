/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/30 23:58:47 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#is_space():	checks if a character is a space character

#Parameters:	char c	

#Return value:	int
	1 if c is a space character, 0 otherwise

#How it works:	
	1. If c is a space character, return 1
	2. Otherwise, return 0
*/
int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

/*
#count_words():	counts the number of words in a string

#Parameters:	char *str_block

#Return value:	int
	the number of words in str_block

#How it works:	
	1. Initialize count to 0
	2. Initialize in_quotes to 0
	3. Skip leading spaces
	4. While *str_block is not NULL
		1. If *str_block is a quote character, toggle in_quotes
		2. If not in_quotes and *str_block is a space character and the next character is not a space character or NULL, increment count
		3. Increment str_block
	5. Return count + 1
*/
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
    return (count + 1);
}

/*
#get_word():	gets the next word from a string

#Parameters:	char **str_block

#Return value:	char*
	the next word in str_block

#How it works:	
	1. Initialize word_start to *str_block
	2. Initialize in_quotes to 0
	3. While **str_block is not NULL and (in_quotes or **str_block is not a space character)
		1. If **str_block is a quote character, toggle in_quotes
		2. Increment *str_block
	4. Return a duplicate of the word from word_start to *str_block
*/
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
	return (my_strndup(word_start, *str_block - word_start));
}

/*
#split_into_words():	splits a string into words

#Parameters:			char *str_block

#Return value:			char**
	an array of words

#How it works:			
	1. Initialize word_count to the number of words in str_block
	2. Allocate memory for words
	3. Initialize i to 0
	4. Skip leading spaces
	5. While i is less than word_count
		1. Skip leading spaces
		2. Get the next word
		3. Skip leading spaces
		4. Increment i
	6. Set the last element of words to NULL
	7. Return words	
*/
char **split_into_words(char *str_block)
{
	int word_count;
	char **words;
	int i;

	i = 0;
	while (*str_block && is_space(*str_block))
		str_block++;
	word_count = count_words(str_block);
	words = malloc(sizeof(char *) * (word_count + 1));
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
