/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:42:29 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 11:31:38 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_bzero():	writes n zeroed bytes to the string str.  If n is zero, 
				ft_bzero() does nothing.

#Parameters:	void *str
				size_t n

#Return value:	void

#How it works:	First creating a temporary char *s1 to change the type of str
				from void * to char *, afterwards it iterates trough n amount
				of bytes and sets them equal to '\0'.
*/

void	ft_bzero(void *str, size_t n)
{
	char	*s1;

	s1 = (char *)str;
	while (n > 0)
	{
		s1[n - 1] = '\0';
		n--;
	}
}
