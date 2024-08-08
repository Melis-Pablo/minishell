/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:14:21 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 17:58:06 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envarg	*init_envarg(t_envarg *envarg, char *arg)
{
	char	*equal;
	char	*key_start;
	char	*key_end;
	char	*value_start;

	equal = strchr(arg, '=');
	key_start = arg;
	if (equal)
	{
		key_end = equal - 1;
		value_start = equal + 1;
	}
	else
	{
		key_end = arg + strlen(arg) - 1;
		value_start = NULL;
	}
	envarg->key = strndup(key_start, key_end - key_start + 1);
	envarg->equal = equal;
	envarg->key_start = key_start;
	envarg->key_end = key_end;
	envarg->value_start = value_start;
	return (envarg);
}

int	env_exist2(t_env *env, char *arg)
{
	t_env		*tmp;
	t_envarg	envarg;
	int			result;

	result = 0;
	tmp = env;
	init_envarg(&envarg, arg);
	while (tmp)
	{
		if (strcmp(tmp->key, envarg.key) == 0)
		{
			if (envarg.equal)
				set_value(tmp, envarg);
			else
				set_value_null(tmp);
			free(envarg.key);
			result = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (result == 0)
		free(envarg.key);
	return (result);
}

void	add_with_value(t_env *node, char *key, char *value_start, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	node->key = key;
	node->value = strdup(value_start);
	node->next = NULL;
	tmp->next = node;
}

void	add_without_value(t_env *node, char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	node->key = key;
	node->value = NULL;
	node->next = NULL;
	tmp->next = node;
}

int	parse_arg(t_env *node, char *arg, t_shell *shell)
{
	t_envarg	envarg;

	init_envarg2(&envarg, arg);
	if (envarg.key_start == envarg.key_end)
		return (1);
	if (envarg.equal)
	{
		add_with_value(node, envarg.key, envarg.value_start, shell->env);
	}
	else
	{
		add_without_value(node, envarg.key, shell->env);
	}
	return (0);
}
