/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:14 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 18:54:40 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_home_path(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	ft_putendl_fd("HOME not set in environment", STDERR_FILENO);
	return (NULL);
}

int	update_pwd2(t_env *env, char *new_pwd)
{
	while (env)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = new_pwd;
			return (0);
		}
		env = env->next;
	}
	free(new_pwd);
	return (1);
}

char	*change_to_home(const char *home_path)
{
	char	*new_pwd;

	if (chdir(home_path) != 0)
	{
		ft_perror("chdir", 1);
		return (NULL);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_perror("getcwd", 1);
		return (NULL);
	}
	return (new_pwd);
}

int	get_home(t_env **env)
{
	char	*home_path;
	char	*new_pwd;

	home_path = find_home_path(*env);
	if (!home_path)
		return (1);
	new_pwd = change_to_home(home_path);
	if (!new_pwd)
		return (1);
	return (update_pwd2(*env, new_pwd));
}

int	get_parent_directory_index(char *str)
{
	int	i;

	i = strlen(str) - 1;
	while (i > 0 && str[i] != '/')
		i--;
	return (i);
}
