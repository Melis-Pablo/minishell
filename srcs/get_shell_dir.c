/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:38:13 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/29 18:56:34 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i++ < len)
		((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
	return (dst);
}

void	ft_copy_backwards(char *dst, const char *src, size_t len)
{
	while (len--)
		dst[len] = src[len];
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_copy_backwards(dst, src, len);
	return (dst);
}

char	*get_shell_dir(t_shell *shell)
{
	char	*shell_dir;
	char	*home_dir;
	size_t	home_len;

	shell_dir = getcwd(0, 0);
	home_dir = get_env_nc(shell->secret_env, "HOME");
	home_len = ft_strlen(home_dir);
	if (ft_strncmp(shell_dir, home_dir, home_len) == 0 && shell_dir)
	{
		shell_dir[0] = '~';
		ft_memmove(shell_dir + 1, shell_dir + home_len,
			ft_strlen(shell_dir + home_len) + 1);
	}
	return (shell_dir);
}
