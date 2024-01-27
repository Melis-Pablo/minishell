/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:29:58 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/14 15:42:09 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_memset():	writes n bytes of value c (converted to an unsigned char) to
				the string s.

#Parameters:	void *s
				int c
				size_t n

#Return value:	returns its first argument.

#How it works:	First creating a temporary char *s1 to change the type of s
				from void * to char *, afterwards it iterates trough n amount
				of bytes and sets them equal to c. At the end returns the
				beggining of the string.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	char	*s1;

	s1 = (char *)s;
	while (n > 0)
	{
		s1[n - 1] = c;
		n--;
	}
	return (s);
}
