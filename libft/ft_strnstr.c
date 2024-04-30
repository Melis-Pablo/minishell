/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:06:40 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 18:09:44 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_strnstr():	locates the first occurrence of the null-terminated string *s2
				in the string *s1, where not more than n characters are
				searched.

#Parameters:	const char *s1
				const char *s2
				size_t n 

#Return:		If *s2 is an empty string, *s1 is returned; if *s2
				occurs nowhere in *s1, NULL is returned; otherwise a
				pointer to the first character of the first occurrence of
				*s2 is returned.

#How it works:	if s2 is null, returns s1. while the main counter is smaller 
				than n and s1 still going, set secondary counter to 0, and
				using another while loop to check for the apperance of s2
				if it reaches the end of s2, inside s1, it returns the start
				of s2 as *s1. if not, return null.
*/

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (i < n && s1[i])
	{
		j = 0;
		while (i + j < n && s1[i + j] == s2[j] && s2[j])
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
