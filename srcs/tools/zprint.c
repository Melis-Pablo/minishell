/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 16:30:25 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#print_all():	prints all strings and words in a 2D array of strings

#Parameters:	char **strings

#Return value:	void

#How it works:	
	1. Initialize i to 0
	2. While strings[i] is not NULL
		1. Print the string
		2. Split the string into words
		3. Initialize j to 0
		4. While words[j] is not NULL
			1. Print the word
			2. Increment j
		5. Increment i
*/
void	print_all(char **strings)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	while (strings[i] != NULL)
	{
		printf("String: >%s<\n", strings[i]);
		words = split_into_words(strings[i]);
		j = 0;
		while (words[j] != NULL)
		{
			printf("Word %d: >%s<\n", j + 1, words[j]);
			j++;
		}
		i++;
	}
}
