/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/05 17:45:00 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_strndup():	Duplicates a string up to n characters

Parameters:		const char *s1 - the string to duplicate
				size_t n - the number of characters to duplicate

Return:			char * - the duplicated string

How it works:
	1. Allocate memory for the new string
	2. Loop through the original string up to n characters
	3. Copy each character to the new string
	4. Add the null terminator
	5. Return the new string
*/
char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
