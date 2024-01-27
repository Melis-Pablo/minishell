/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:25:49 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/14 16:50:22 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_strlcpy():	copies (size) amount of bytes of memory to the *dst

#Parameters:	char *dst
				const char *src
				size_t size

#Return:		src_len

#How it works:	the function calls ft_strlen() function to determine the src
				length, using a while loop the function copies (size) amount
				of bytes to the *dst pointer.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	i;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
