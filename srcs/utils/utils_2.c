/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:36:20 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 18:01:20 by pmelis           ###   ########.fr       */
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

/*
ft_strncpy():	Copies a string up to n characters

Parameters:		char *dst - the destination string
				const char *src - the source string
				size_t n - the number of characters to copy

Return:			char * - the destination string

How it works:
	1. Loop through the source string up to n characters
	2. Copy each character to the destination string
	3. Add the null terminator
	4. Return the destination string
*/
char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
ft_strlen():	Calculates the length of a string

Parameters:		const char *s - the string to calculate the length of

Return:			size_t - the length of the string

How it works:
	1. Loop through the string
	2. Increment a counter for each character
	3. Return the counter
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
ft_strcat():	Concatenates two strings

Parameters:		char *dst - the destination string
				const char *src - the source string

Return:			char * - the destination string

How it works:
	1. Loop through the destination string
	2. Find the null terminator
	3. Loop through the source string
	4. Copy each character to the destination string
	5. Add the null terminator
	6. Return the destination string
*/
char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

/*
ft_strcmp():	Compares two strings

Parameters:		const char *s1 - the first string
				const char *s2 - the second string

Return:			int - 0 if the strings are equal, otherwise the difference

How it works:
	1. Loop through the strings
	2. Compare each character
	3. If the characters are different, return the difference
	4. If one string ends before the other, return the difference in length
	5. If the strings are equal, return 0
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
