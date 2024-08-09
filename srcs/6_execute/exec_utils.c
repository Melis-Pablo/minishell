/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:10:08 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 16:26:32 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_internal(t_shell *shell, t_cmd *cmd, int *status)
{
	char	*path;

	if (builtins_caller(shell, cmd, status) == 0)
		return (0);
	path = get_exec_path(cmd->cmd, shell->env);
	if (path)
	{
		free(cmd->cmd);
		cmd->cmd = path;
		*status = exec_child(cmd, shell->env);
		return (0);
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd("\n", 2);
	*status = 127;
	return (1);
}

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 1;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	free_pl_ret(void *pl, int ret)
{
	free(pl);
	return (ret);
}
