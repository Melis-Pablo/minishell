/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:29:20 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/16 14:11:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
#ft_putendl_fd():	Writes a string and a newline to the indicated file.

#Parameters:		char *s
					int fd

#Return value:		void

#How it works:		writes the string s using ft_putstr_fd() and a newline with
					ft_putchar_fd()

*/

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
