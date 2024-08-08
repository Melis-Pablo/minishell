/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:14:17 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 13:58:18 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

void	ft_reverse_str(char *str, int len)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

void	ft_itoa(int n, char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = (n < 0);
	if (n == 0)
		str[i++] = '0';
	if (sign)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	ft_reverse_str(str, i);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = 0;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}


void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*(s++), fd);
}


void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

char	*ft_strchr(const char *s, int chr)
{
	unsigned char	c;

	if (!s)
		return (0);
	c = (unsigned char)chr;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (!c)
		return ((char *)s);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
		((unsigned char *) dst)[i - 1] = ((unsigned char *) src)[i - 1];
	return (dst);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*p;

	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (start < slen)
	{
		p = malloc(len + 1);
		ft_memcpy(p, (s + start), len);
		p[len] = 0;
	}
	else
	{
		p = malloc(1);
		*p = 0;
	}
	return (p);
}
