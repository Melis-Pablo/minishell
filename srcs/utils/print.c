/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/08 15:58:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array():	Prints an array of strings

Parameters:			char **arr - the array of strings to print

Return:				void

How it works:
	1. Loop through the array of strings
	2. Print each string
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
