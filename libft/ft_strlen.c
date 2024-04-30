/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:25:11 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:51:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_strlen():	find length of string.

#Parameters:	const char *str

#Return value:	returns number of characters in str (excluding null).

#How it works:	Uses counter and a while loop to cycle trough the string until
				the end and returns the counter.
*/

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
