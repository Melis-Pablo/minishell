/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:07:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/07/23 04:31:25 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
m_env():	env command

Arguments:	t_cmd *cmd

Return:		int exit status

How it works:
				1. loop envs
					2. if there is key or value print both
					3. if there is only one of those print key
				4. return 0
*/
int	m_env(t_cmd *cmd)
{
	t_env	*env;

	env = cmd->env;

	while (env != NULL)
	{
		if (env->value != NULL || env->value[0] != '\0')
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		else
		{
			printf("%s\n", env->key);
			env = env->next;
		}
	}
	return (0);
}

int	set_env_lst(t_cmd *cmd_list,t_env *env)
{
	t_cmd *tmp;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		cmd_list->env = env;
		tmp = tmp->next;
	}
	return (0);
}