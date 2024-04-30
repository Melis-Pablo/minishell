/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:03:41 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 18:03:20 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_memchr():	function scans the initial n bytes of the memory area pointed
				to by s for the first instance of c.

#Parameters:	const void *s
				int c
				size_t n

#Return value:	void *

#How it works:	using a while loop it looks for the first occurrance and returns
				the pointer to it.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*(str + i) == chr)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
