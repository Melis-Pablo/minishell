/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:12:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:01:33 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while ((dstsize - 1) > i && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
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
