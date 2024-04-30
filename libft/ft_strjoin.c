/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:13:59 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 18:28:23 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_strjoin():	the function joins the strings s1 and s2 and returns the joined
				string

#Parameters:	const char *s1
				const char *s2

#Return value:	str or NULL if the allocation fails

#How it works:	allocates memory with found size, using while loops,
				copies both strings to new str variable, and ends it with \0
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(sizeof(char) * (size));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
