/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 19:01:55 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_key(t_envarg *envarg, char *arg)
{
	char	*equal;

	equal = strchr(arg, '=');
	envarg->key_start = arg;
	if (equal)
	{
		envarg->key_end = equal - 1;
	}
	else
	{
		envarg->key_end = arg + strlen(arg) - 1;
	}
	envarg->key = strndup(envarg->key_start,
			envarg->key_end - envarg->key_start + 1);
	envarg->equal = equal;
}

void	init_value(t_envarg *envarg, char *arg)
{
	if (envarg->equal)
	{
		envarg->value_start = envarg->equal + 1;
		envarg->value_end = arg + strlen(arg);
	}
	else
	{
		envarg->value_start = NULL;
		envarg->value_end = NULL;
	}
}

t_envarg	*init_envarg2(t_envarg *envarg, char *arg)
{
	init_key(envarg, arg);
	init_value(envarg, arg);
	return (envarg);
}

int	handle_export_arg(t_shell *shell, char *arg, int *result)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (ft_perror("malloc", 1));
	node->next = NULL;
	if (env_exist2(shell->env, arg) == 1)
	{
		free(node);
		return (0);
	}
	if (parse_arg(node, arg, shell) != 0)
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		free(node);
		*result = 1;
		return (1);
	}
	sort(&shell->env);
	return (0);
}

int	m_export(t_shell *shell, t_cmd *cmd)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (flag_checker(cmd->args))
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while (cmd->args[i])
	{
		if (handle_export_arg(shell, cmd->args[i], &result) != 0)
		{
			result = 1;
		}
		i++;
	}
	if (cmd->args[0] == NULL)
		print_env_list_export(shell->env);
	return (result);
}
