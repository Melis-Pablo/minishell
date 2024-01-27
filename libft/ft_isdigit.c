/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:11:27 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:46:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_isdigit():	decimal-digit character test.

#Parameters:	int c

#Return value:	returns zero if the character tests false and
				returns non-zero if the character tests true.

#How it works:	Compares the value of c to determine if it falls between
				(0 & 9) on the ascii table.
*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
