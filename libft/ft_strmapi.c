/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:23:01 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 20:51:07 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_strmapi():		applies the function ’f’ to each character of the string ’s’
					to create a new string resulting from successive applications
					of ’f’.

#Parameters:		char const *s
					char (*f)(unsigned int, char)

#Return value:		char *

#How it works:		first it duplicates the string s, then checks for invalid
					inputs and memory allocation fails, after it applies the 
					function to each character and returns the new string after
					the function was applied.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	str = ft_strdup(s);
	i = 0;
	if (!s || !f ||!str)
		return (NULL);
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
