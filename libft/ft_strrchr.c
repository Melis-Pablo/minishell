/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:00:46 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 17:58:56 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_strrchr():	locates the last occurrence of c (converted to a char) in the
				string pointed to by s.

#Parameters:	char *s
				int c

#Return:		pointer to the located character, or NULL if the character does
				not appear in the string.

#How it works:	first it gets the size of s. while a is bigger than 0, if s= c
				return s[a], if not keep decreasing a, if c = \0 return the end
				of s, if not found return null.
*/

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen((char *)s);
	while (a >= 0)
	{
		if (s[a] == (char)c)
			return ((char *)s + a);
		a--;
	}
	if (c == '\0' && s[a] == (char)c)
		return ((char *)s + a);
	return (NULL);
}
