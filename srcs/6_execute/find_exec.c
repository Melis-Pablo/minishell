/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:47:35 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 13:58:21 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
