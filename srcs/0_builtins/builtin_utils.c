/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:18:32 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/05 21:13:57 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_error_name(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			return (0);
		if (args[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	flag_checker(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	env_exists(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	*init_envarg(t_envarg *envarg, char *arg)
{
	envarg->equal = strchr(arg, '=');
	envarg->key_start = arg;
	envarg->key_end = envarg->equal - 1;
	envarg->value_start = envarg->equal + 1;
	envarg->key = strndup(envarg->key_start,
			envarg->key_end - envarg->key_start + 1);
	return (envarg);
}

int	env_exist2(t_env *env, char *arg)
{
	t_env		*tmp;
	t_envarg	envarg;

	init_envarg(&envarg, arg);
	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, envarg.key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(envarg.value_start);
			free(envarg.key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(envarg.key);
	return (0);
}
