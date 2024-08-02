/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:59:06 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 20:33:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



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



char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*p;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	p = malloc(len1 + len2 + 1);
	if (!p)
		return (0);
	ft_strlcpy(p, s1, len1 + 1);
	ft_strlcpy(p + len1, s2, len2 + 1);
	return (p);
}

int	ft_env_size(t_env *env)
{
	int		size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**export_env(t_env *env)
{
	char	**envp;
	int		i;
	char	*key_equal;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	while (env)
	{
		key_equal = ft_strjoin(env->key, "=");
		if (!key_equal)
		{
			free_array(envp);
			return (0);
		}
		envp[i] = ft_strjoin(key_equal, env->value);
		if (!envp[i])
		{
			free_array(envp);
			free(key_equal);
			return (0);
		}
		free(key_equal);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

// void	set_env(t_shell *shell, char *key, const char *value)
// {
// 	t_env	*env;

// 	env = shell->env;
// 	while (env)
// 	{
// 		if (ft_strcmp(env->name, key) == 0)
// 		{
// 			free(env->value);
// 			env->value = ft_strdup(value);
// 			return ;
// 		}
// 		env = env->next;
// 	}
// 	env = malloc(sizeof(t_env));
// 	env->name = ft_strdup(key);
// 	env->value = ft_strdup(value);
// 	env->next = shell->env;
// 	shell->env = env;
// 	shell->envc++;
// }

// void	set_secret_env(t_shell *shell, char *key, const char *value)
// {
// 	t_env	*env;

// 	env = shell->secret_env;
// 	while (env)
// 	{
// 		if (ft_strncmp(env->name, key, ft_strlen(key)) == 0)
// 		{
// 			free(env->value);
// 			env->value = ft_strdup(value);
// 			return ;
// 		}
// 		env = env->next;
// 	}
// 	env = malloc(sizeof(t_env));
// 	env->name = ft_strdup(key);
// 	env->value = ft_strdup(value);
// 	env->next = shell->secret_env;
// 	shell->secret_env = env;
// 	shell->secret_envc++;
// }