/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:59:57 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 18:53:37 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_perror(char *str, int i)
{
	perror(str);
	return (i);
}

int	update_pwd3(t_env *env, const char *new_pwd)
{
	free (env->value);
	env->value = strdup(new_pwd);
	if (!env->value)
		return (1);
	if (chdir(env->value) != 0)
	{
		free(env->value);
		return (1);
	}
	return (0);
}

int	process_pwd_entry(t_env *env)
{
	int		index;
	char	*new_pwd;

	index = get_parent_directory_index(env->value);
	if (index <= 0)
		return (1);
	new_pwd = strndup(env->value, index);
	if (!new_pwd)
		return (1);
	if (update_pwd3(env, new_pwd) != 0)
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

int	get_up(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env != NULL)
	{
		if (strcmp(env->key, "PWD") == 0)
			return (process_pwd_entry(env));
		env = env->next;
	}
	return (1);
}
