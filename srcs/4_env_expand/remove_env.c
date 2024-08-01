/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:48:55 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 17:49:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	remove_env(t_shell *shell, const char *key)
{
	t_env	*env;
	t_env	*last;

	env = shell->env;
	last = 0;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			if (last)
				last->next = env->next;
			else
				shell->env = env->next;
			free(env->name);
			free(env->value);
			free(env);
			shell->envc--;
			return ;
		}
		last = env;
		env = env->next;
	}
}

void	remove_secret_env(t_shell *shell, const char *key)
{
	t_env	*env;
	t_env	*last;

	env = shell->secret_env;
	last = 0;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			if (last)
				last->next = env->next;
			else
				shell->secret_env = env->next;
			free(env->name);
			free(env->value);
			free(env);
			shell->secret_envc--;
			return ;
		}
		last = env;
		env = env->next;
	}
}
*/