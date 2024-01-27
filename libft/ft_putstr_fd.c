/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:28:28 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/15 21:55:09 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
#ft_putstr_fd():	Writes a string to the indicated file.

#Parameters:		char *s
					int fd

#Return value:		void

#How it works:		using the write function, writes s, to the file descriptor
					fd, using the ft_strlen() to calculate the size.
*/

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
