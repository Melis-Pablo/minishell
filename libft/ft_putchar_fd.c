/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:13 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/15 20:26:52 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
#ft_putchar_fd():	Writes a character to the indicated file.

#Parameters:		char c
					int fd

#Return value:		void

#How it works:		using the write funtion writes what is on the adress of c
					to the indicated file descriptor both passed as a parameter
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
