/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:04:49 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/09 18:40:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_memcmp():	this function compares n amount of bytes of memory areas of s1
				and s2 and returns the diffetence

Parameters: const void *s1
			const void s2
			Size_t n

Return: char *s pointer of found character or null if it is not found

How it works:	compares the mem of s1 to s2 and returns the difference.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ch1;
	const unsigned char	*ch2;

	ch1 = s1;
	ch2 = s2;
	i = 0;
	while (i < n)
	{
		if (ch1[i] != ch2[i])
			return (ch1[i] - ch2[i]);
		i++;
	}
	return (0);
}
