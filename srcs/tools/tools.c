/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 17:41:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_strndup:		duplicate a string up to n characters

Parameters:		const char *s1 - the string to duplicate
				size_t n - the number of characters to duplicate

Return:			char * - the duplicated string

How it works:
	1. Allocate memory for the new string
	2. Copy the characters from s1 to the new string up to n characters
	3. Add a null terminator at the end
	4. Return the new string
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
