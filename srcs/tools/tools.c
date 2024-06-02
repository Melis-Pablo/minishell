/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 18:01:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ft_strndup():	duplicates a string up to n characters
char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
