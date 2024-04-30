/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:50:35 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/24 18:51:02 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n, char c)
{
	int		i;
	char	*s;

	i = 0;
	if (c == 'X')
		s = "0123456789ABCDEF";
	else
		s = "0123456789abcdef";
	if (c == 'p')
	{
		i += ft_putstr("0x");
		c = 0;
	}
	if (n < 16)
		i += ft_putchr(s[n]);
	else
	{
		i += ft_puthex(n / 16, c);
		i += ft_puthex(n % 16, c);
	}
	return (i);
}
