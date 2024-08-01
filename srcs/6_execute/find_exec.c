/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:47:35 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 20:07:33 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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


char	*join_paths(const char *dir, const char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = (char *)malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	strcpy(full_path, dir);
	full_path[dir_len] = '/';
	strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

char	*find_executable_in_path(char *name, const char *path)
{
	const char	*p;
	const char	*end;
	char		*full_path;
	char		*tmp;

	p = path;
	while (*p)
	{
		end = ft_strchr(p, ':');
		if (!end)
			end = p + ft_strlen(p);
		if (end - p > 0)
		{
			tmp = ft_substr(p, 0, end - p);
			full_path = join_paths(tmp, name);
			free(tmp);
			if (full_path && access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
		}
		p++;
	}
	return (0);
}

char	*get_exec_path(char *name, t_env *env)
{
	const char	*path;
	struct stat	file_stat;

	if (ft_strchr(name, '/') != 0 || name[0] == '.')
	{
		if (access(name, X_OK) == 0 && stat(name, &file_stat) == 0
			&& !S_ISDIR(file_stat.st_mode))
			return (ft_strdup(name));
		return (0);
	}
	path = get_env_nc(env, "PATH");
	if (!path)
		return (0);
	return (find_executable_in_path(name, path));
}


// char	*find_command(char *cmd)
// {
// 	char	*path_env;
// 	char	**paths;
// 	char	*full_path;
// 	int		i;

// 	if (is_executable(cmd))
// 		return (ft_strdup(cmd));
// 	path_env = getenv("PATH");
// 	paths = ft_split(path_env, ':');
// 	if (!path_env || !paths)
// 		return (NULL);
// 	i = -1;
// 	while (paths[++i])
// 	{
// 		full_path = join_paths(paths[i], cmd);
// 		if (full_path && is_executable(full_path))
// 		{
// 			free(paths);
// 			return (full_path);
// 		}
// 		free(full_path);
// 	}
// 	free(paths);
// 	return (NULL);
// }

// /////////////