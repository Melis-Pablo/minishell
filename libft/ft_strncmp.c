/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:02:37 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/09 18:37:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_strncmp():	the string compares n size of bytes in the memory pointed by s1
				and compares it with s2 to return the difference of the first
				character difference found 

Parameters:		const char *s1
				const char *s2
				size_t n

Return: the differences between the values of the first different character
		found in the comparison of s1 and s2 

How it works:	the function parses through both s1 and s2 strings with a while
				function to compare the values, when a diference is found or n
				has reached its limit or either of the string is finished and
				return the diference 
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (i + 1 < n) && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
