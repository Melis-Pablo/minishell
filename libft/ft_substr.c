/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:12:51 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 18:23:36 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_substr():	Returns the substring of the given string at the given start
				position with the given length (or smaller if the length of
				the original string is less than start + len.

#Parameters:	char const *s
				unsigned int start
				size_t len

#Return:		char *

#How it works:	first it gets slen, if start is bigger than slen, return empty
				str, if slen - start is smaller than len, set len to slen - 
				start. allocate the memory using len +1. is allocation fails
				return null, if not use ft_strlcpy to copy it to *str and
				return it.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if ((slen - start) < len)
		len = slen - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)(s + start), len + 1);
	return (str);
}
