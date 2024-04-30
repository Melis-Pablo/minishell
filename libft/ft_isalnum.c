/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:10:09 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:49:47 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_isalnum():	alphanumeric character test.

#Parameters:	int c

#Return value:	returns zero if the character tests false and
				returns non-zero if the character tests true.

#How it works:	The function tests for any character for which ft_isalpha() or
				ft_isdigit() is true.
*/

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (c);
	return (0);
}
