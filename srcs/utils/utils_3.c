/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:17:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/11 14:18:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_strdup():	Duplicates a string

Parameters:		const char *s - the string to duplicate

Return:			char * - the duplicated string

How it works:
	1. Allocate memory for the new string
	2. Copy the characters from the original string to the new string
	3. Add a null terminator at the end of the new string
	4. Return the new string
*/
char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
