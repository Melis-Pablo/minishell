/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 16:31:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#my_strndup():	duplicates a string up to n characters

#Parameters:	const char* s, size_t n

#Return value:	char*
	the duplicated string

#How it works:	
	1. Initialize len to 0
	2. Initialize i to 0
	3. While s[len] is not NULL and len is less than n, increment len
	4. Allocate memory for a new string of size len + 1
	5. If allocation fails, return NULL
	6. While i is less than len, copy s[i] to new_str[i]
	7. Set new_str[i] to NULL
	8. Return new_str
*/
char	*my_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	len = 0;
	i = 0;
	while (s[len] != '\0' && len < n)
		len++;
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
