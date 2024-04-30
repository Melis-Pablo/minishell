/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:07:40 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/21 17:26:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_atoi():		Converts the initial portion of the string pointed to by str to
				int representation.

#Parameters:	const char *str

#Return value:	int representation of str

#How it works:	The function first skips the white spaces, aftewards checks for
				a negative sign and sets the sign variable respectively. After
				it will store each number in the result variable to finally
				return the result multiplied by the sign.
*/

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == (' ') || str[i] == ('\t') || str[i] == ('\n')
		|| str[i] == ('\v') || str[i] == ('\f') || str[i] == ('\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - '0';
	return (sign * result);
}
