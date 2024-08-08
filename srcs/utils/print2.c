/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:03:41 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:03:57 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_env_list_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value != NULL)
			printf("=\"%s\"\n", tmp->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
}
