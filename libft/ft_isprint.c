/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:11:36 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 11:11:59 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_isprint():	printing character test.

#Parameters:	int c

#Return value:	returns zero if the character tests false and
				returns non-zero if the character tests true.

#How it works:	Checks if c falls between 32 and 126 which correspond to the
				ascii table printable characters.
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
