/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:49:32 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 11:40:49 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_memcpy():		copies n bytes from memory area src to memory area dst.

#Parameters:		void *dst
					const void *src
					size_t n

#Return value:		returns the original value of dst.

#How it works:		First src and dst are converted to char *, then it checks
					if they are already equal or n = 0 and returns dst, if they
					are both null returns 0. Finally if non are the case it uses
					a while loop to copy the values from src to dst and returns
					dst.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tsrc;
	char	*tdst;

	tsrc = (char *)src;
	tdst = (char *)dst;
	if ((src == dst) || n == 0)
		return (dst);
	if (!src && !dst)
		return (0);
	while (n--)
		tdst[n] = tsrc[n];
	return (dst);
}
