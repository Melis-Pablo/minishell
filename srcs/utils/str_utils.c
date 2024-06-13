/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:51:57 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 14:00:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_strndup:	Duplicates the string s1 up to n characters.

Parameters:	const char *s1 - the string to duplicate.
			size_t n - the number of characters to duplicate.

Return:		char *dup - the duplicated string.

How it works:
	1. Allocate memory for the new string dup.
	2. Loop through the string s1 until the null terminator is reached or n
		characters are copied.
	3. Copy the characters from s1 to dup.
	4. Add the null terminator to dup.
	5. Return dup.
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
ft_strdup:	Duplicates the string s.

Parameters:	const char *s - the string to duplicate.

Return:		char *str - the duplicated string.

How it works:
	1. Allocate memory for the new string str.
	2. Loop through the string s until the null terminator is reached.
	3. Copy the characters from s to str.
	4. Add the null terminator to str.
	5. Return str.
*/
char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
ft_strncpy:	Copies the string src to dst up to n characters.

Parameters:	char *dst - the destination string.
			const char *src - the source string.
			size_t n - the number of characters to copy.

Return:		char *dst - the destination string.

How it works:
	1. Loop through the string src until the null terminator is reached or n
		characters are copied.
	2. Copy the characters from src to dst.
	3. Add the null terminator to dst.
	4. Return dst.
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
ft_strcat:	Concatenates the string src to the end of the string dst.

Parameters:	char *dst - the destination string.
			const char *src - the source string.

Return:		char *dst - the destination string.

How it works:
	1. Get the length of the string dst.
	2. Loop through the string src until the null terminator is reached.
	3. Copy the characters from src to the end of dst.
	4. Add the null terminator to dst.
	5. Return dst.
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
ft_strcmp:	Compares the strings s1 and s2.

Parameters:	const char *s1 - the first string to compare.
			const char *s2 - the second string to compare.

Return:		int - 0 if the strings are equal, a positive number if s1 is

How it works:
	1. Loop through the strings s1 and s2 until the null terminator is reached
		or the characters are different.
	2. Return the difference between the characters at the current position.
	3. If the strings are equal, return 0.
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
