/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:04 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/05 17:37:32 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_variable(t_shell *shell, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (strncmp(current->key, var, ft_strlen(current->key) + 1) == 0)
		{
			if (prev == NULL)
				shell->env = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	m_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[0] == NULL)
		return (0);
	while (cmd->args[i])
	{
		if (strchr(cmd->args[i], '='))
		{
			ft_putstr_fd("unset:", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("invalid argument", STDERR_FILENO);
			shell->last_status = 1;
		}
		else
		{
			if (remove_variable(shell, cmd->args[i]) != 1)
				shell->last_status = 0;
		}
		i++;
	}
	return (shell->last_status);
}
