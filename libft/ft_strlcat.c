/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:25:22 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/09 18:38:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_strlcat():	this function concatenates the src and dst up to (size) bytes

#Parameters:	char *dest
				const char *src
				size_t size

#Return:		length of created string 

#How it works:	First gets the length of src. if size = 0 return srclen, after
				it gets the offset of the destination (j) than it copies until
				the end of src or it reaches size, at the end it closes it with
				a null terminator and if the offset is bigger than the size,
				return src + len, if not return offset +src len which is the 
				final length
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	j;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (dest[j])
		j++;
	while (src[i] && j + i < size - 1)
	{
		dest[i + j] = src[i];
		i++;
	}
	if (i < size)
		dest[j + i] = '\0';
	if (j > size)
		return (src_len + size);
	return (j + src_len);
}
