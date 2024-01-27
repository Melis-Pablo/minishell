/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:45:22 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/24 18:45:49 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (write(1, "(null)", 6));
	while (args[i])
		ft_putchr(args[i++]);
	return (i);
}
