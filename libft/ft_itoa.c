/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:21:41 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 20:45:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_itoa():		constructs a string representation of an integer.

#Parameters:	int n

#Return value:	*dst
				0 if the allocation  fails.

#How it works:	The ft_intlen() function determines the length of the resulting
				string and allocates memory for the string. The ft_itoa()
				function then uses this length to construct the string. It
				checks if the integer 'n' is 0 or negative. If 'n' is 0, it
				sets the first character of the string to '0'. If 'n' is
				negative, it sets the first character of the string to '-' and
				changes 'n' to its absolute value. It then uses a while loop to
				convert each digit of 'n' into a character and store it in the
				allocated memory. Finally, it adds a null terminator to the end
				of the string.
*/

static int	ft_intlen(char **chrnum, int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num == 0)
		len = 2;
	if (num < 0 || num > 0)
	{
		while (num)
		{
			num /= 10;
			len++;
		}
		len++;
		num = n;
		if (num < 0)
			len++;
	}
	*chrnum = (char *)malloc(sizeof(char) * len);
	return (len);
}

char	*ft_itoa(int n)
{
	char	*chrnum;
	int		len;
	long	num;

	chrnum = NULL;
	len = ft_intlen(&chrnum, n);
	if (chrnum == NULL)
		return (NULL);
	num = n;
	if (num == 0)
		*(chrnum + 0) = '0';
	if (num < 0)
	{
		*(chrnum + 0) = '-';
		num = -num;
	}
	*(chrnum + len - 1) = '\0';
	while (num)
	{
		*(chrnum + len - 2) = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (chrnum);
}
