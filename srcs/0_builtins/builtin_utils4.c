/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:52:18 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/06 18:34:59 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	lst_swap_next(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env || !(*env)->next)
		return ;
	tmp = (*env)->next;
	(*env)->next = (*env)->next->next;
	tmp->next = *env;
	(*env) = tmp;
}

void	sort(t_env **env)
{
	t_env	**a;
	int		i;
	int		len;

	if (!env || !*env || !(*env)->next)
		return ;
	len = get_env_length(*env);
	while (len > 1)
	{
		a = env;
		i = 0;
		while (a != NULL && (*a)->next != NULL && i < len)
		{
			if (strcmp((*a)->key, (*a)->next->key) > 0)
				lst_swap_next(a);
			a = &(*a)->next;
			i++;
		}
		len--;
	}
}

int	check_flag(t_cmd *cmd)
{
	if (flag_checker(cmd->args))
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
