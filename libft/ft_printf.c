/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:56:24 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/24 18:56:27 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_printf_checker():	the function checks which type of conversion is called
						and prints it with the respective function.

#Parameters:			char s
						va_list *args
						int *i

#Return:				int -- amount of chr printed

#How it works:			the function takes the current char of the format string
						and checks for which conversion it needs, it will use
						its corresponding function using the following argument
						using va_arg, and return the amount of chr printed. if
						it is not any of the supported identifiers it will go
						back so it prints that char in the next loop of printf.
*/

int	ft_printf_checker(char s, va_list *args, int *i)
{
	if (s == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (s == 'd' || s == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (s == 'u')
		return (ft_putunsigned(va_arg(*args, unsigned int)));
	else if (s == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), s));
	else if (s == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), s));
	else if (s == 'p')
		return (ft_puthex(va_arg(*args, size_t), s));
	else if (s == 'c')
		return (ft_putchr(va_arg(*args, int)));
	else if (s == '%')
		return (ft_putchr('%'));
	else
	{
		(*i)--;
		return (1);
	}
}

/*
#ft_printf():	recreation of printf() with conversions (cspdiuxX%)

#Parameters:	const char *format
				...

#Return:		int length -- amount of chr printed

#How it works:	it starts the va_list with va_start and the last arg (format).
				it loops until the format string is over, in that loop it checks
				when '%' and calls the ft_printf_checker() and increases i. it
				writes each chr until its done. ends the va_list with va_end
				and finally returns the length.
*/

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		length;

	i = 0;
	length = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			length += ft_printf_checker(format[i], &args, &i);
			i++;
		}
		else
		{
			length += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (length);
}
