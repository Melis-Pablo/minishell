/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:10:41 by pmelis            #+#    #+#             */
/*   Updated: 2023/01/27 15:00:46 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_isascii():	test for ASCII character.

#Parameters:	int c

#Return value:	returns zero if the character tests false and
				returns non-zero if the character tests true.

#How it works:	Checks if c falls between 0 and 127 which correspond to the
				ascii table characters.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
