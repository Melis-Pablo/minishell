/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:59:02 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/02 14:47:18 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_toupper():	lower case to upper case letter conversion.

#Parameters:	int c

#Return:		If the argument is a lower-case letter, the toupper() function
				returns the corresponding upper-case letter if there is one;
				otherwise, the argument is returned unchanged.

#How it works:	the function calls an if statement which will execute if the
				value of c falls between the lowercase values in the ascii table
				and decrease the value by 32 to convert it to uppercase.
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
