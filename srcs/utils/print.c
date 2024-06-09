/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 19:04:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array():	Prints an array of strings

Parameters:			char **arr - the array of strings to print

Return:				void

How it works:
	1. Loop through the array of strings
	2. Print each string with an index
*/
void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("Word[%i] %s\n", i, arr[i]);
		i++;
	}
	printf("\n");
}

/*
print_strings_and_words():	Prints the strings and words from the input

Parameters:					char *input - the input string

Return:						void

How it works:
	1. Split the input by pipes
	2. Loop through the strings
	3. Print the string
	4. Split the string into words
	5. Clean the quotes in the words
	6. Print the words
	7. Free the words
	8. Free the strings
*/
void	print_strings_and_words(char *input)
{
	char	**strings;
	char	**words;
	int		i;

	strings = split_by_pipes(input);
	i = 0;
	while (strings[i] != NULL)
	{
		printf("string: %s\n", strings[i]);
		words = split_into_words(strings[i]);
		if (!words)
		{
			free_array(strings);
			return ;
		}
		//clean_quotes_in_array(words);
		print_str_array(words);
		free_array(words);
		i++;
	}
	free_array(strings);
}
