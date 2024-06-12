/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:17:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/12 17:24:15 by pmelis           ###   ########.fr       */
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

/*
ft_isalnum():	Checks if a character is an alphanumeric character

Parameters:		int c - the character to check

Return:			int - 1 if the character is alphanumeric, 0 otherwise

How it works:
	1. Check if the character is a digit
	2. Check if the character is an uppercase letter
	3. Check if the character is a lowercase letter
	4. Return 1 if any of the above checks are true, 0 otherwise
*/
int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}
