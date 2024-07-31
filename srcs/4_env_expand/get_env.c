/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:06 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/31 17:27:40 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	load_env(t_cmd *cmd, char **envp)
{
	char	**env;
	char	*key;
	char	*value;

	env = envp;
	// cmd->envc = 0;
	// cmd->secret_envc = 0;
	while (*env)
	{
		parse_env_var(*env, &key, &value);
		set_env(shell, key, value);
		set_secret_env(shell, key, value);
		free(key);
		env++;
	}
}

char	*get_env(t_env *env, char *key)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (0);
}

const char	*get_env_nc(t_env *env, char *key)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, key, ft_strlen(key)) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (0);
}

char	**export_env(t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize((t_list *) env) + 1));
	if (!envp)
		return (0);
	while (env)
	{
		envp[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		if (!envp[i])
		{
			free(envp);
			return (0);
		}
		env = env->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}
