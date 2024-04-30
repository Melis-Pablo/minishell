/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:23:39 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/14 17:23:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_striteri():	The function iterates trough each byte of memory and passes it 
				trough the function given

#Parameters:	char *s
				void (*f)(unsigned int, char*)

#Return value:	VOID

#How it works:	the function takes the bytes of memory on the given s pointer
				and passes them trough the function passed as a parameter
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
