/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:07:20 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/04 17:10:15 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env != NULL)
	{
		if (env->value != NULL || env->value[0] != '\0')
		{
			printf("%s=%s\n", env->key, env->value);
		}
		// else
		// {
		// 	// printf("%s\n", env->key);
		// }
		env = env->next;
	}
	return (0);
}
