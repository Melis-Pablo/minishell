/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:09:11 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/09 17:21:18 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_calloc():	contiguously allocates enough space for nelem objects that are
				elsize bytes of memory each and returns a pointer to the allocated
				memory. The allocated memory is filled with bytes of value zero.

#Parameters:	size_t nelem
				size_t elsize

#Return value:	void *ptr

#How it works:	Creates pointer and allocates its memory using malloc() using
				nelem and elsize to determine the amount of bytes to allocate
				if the pointer is null after the allocation it will return NULL
				if not, the funtion will fill the bytes using ft_bzero() and
				finally returns the pointer.
*/

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	ptr = malloc(nelem * elsize);
	if (!ptr || elsize >= 65535 || nelem >= 65535)
		return (NULL);
	ft_bzero(ptr, nelem * elsize);
	return (ptr);
}
