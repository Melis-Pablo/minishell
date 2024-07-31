/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:47:35 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/23 06:48:04 by pmelis           ###   ########.fr       */
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

int	is_executable(const char *path)
{
	struct stat	sb;

	return (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR);
}

char	*find_command(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (is_executable(cmd))
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	if (!path_env || !paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_paths(paths[i], cmd);
		if (full_path && is_executable(full_path))
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
	}
	free(paths);
	return (NULL);
}
