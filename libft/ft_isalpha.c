/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:03:49 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:45:46 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_isalpha():	alphabetic character test.

#Parameters:	int c

#Return value:	returns zero if the character tests false and 
				returns non-zero if the character tests true.

#How it works:	Compares the value of c to determine if it falls between
				(a & z) or (A & Z) on the ascii table.
*/

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
