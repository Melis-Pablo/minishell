/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:18:32 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 16:18:08 by grbuchne         ###   ########.fr       */
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

void	set_value(t_env *tmp, t_envarg envarg)
{
	free(tmp->value);
	tmp->value = strdup(envarg.value_start);
}

void	set_value_null(t_env *tmp)
{
	free(tmp->value);
	tmp->value = NULL;
}
