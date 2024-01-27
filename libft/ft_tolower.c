/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:59:02 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:46:58 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_tolower():	upper case to lower case letter conversion.

#Parameters:	int c

#Return:		If the argument is an upper-case letter, the tolower() function
				returns the corresponding lower-case letter if there is one;
				otherwise, the argument is returned unchanged.

#How it works:	the function calls an if statement which will execute if the
				value of c falls between the uppercase values in the ascii
				table and increase the value by 32 to convert it to lowercase.
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
