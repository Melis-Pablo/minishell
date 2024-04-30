/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:31:18 by pmelis            #+#    #+#             */
/*   Updated: 2022/12/15 21:52:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
#ft_putnbr_fd():	Writes a number to the desired file.

#Parameters:		int n
					int fd

#Return value:		void

#How it works:		First it check for the edge case of the min int and writes
					it to the file using the file descriptor and ft_putstr_fd()
					if the number is negative it will write the negative sign
					using the file descriptor and ft_putchr_fd() and then
					recursively call itself with the positive version of the
					n. If the number is bigger then 10 it will print the last
					digit using ft_putchr_fd() and recursively continue with
					the remainder of the digits, it will keep calling itself
					until it reaches the last digit and writes it with 
					ft_putchr_fd().
*/

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
