/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:48:29 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/24 18:48:47 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsigned(unsigned int u)
{
	int	i;

	i = 0;
	if (u >= 10)
		i += ft_putunsigned(u / 10);
	i += ft_putchr(u % 10 + '0');
	return (i);
}
