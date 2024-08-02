/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:13:29 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 22:04:24 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_caller(t_shell *shell, t_cmd *cmd, int *status)
{
	if (strcmp(cmd->cmd, "pwd") == 0)
	{
		*status = m_pwd(cmd);
		return (1);
	}
	if (strcmp(cmd->cmd, "echo") == 0)
	{
		*status = m_echo(cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "cd") == 0)
	{
		*status = m_cd(shell, cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "export") == 0)
	{
		*status = m_export(shell, cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "unset") == 0)
	{
		*status = m_unset(shell, cmd);
		return (1);
	}
	else if (strcmp(cmd->cmd, "env") == 0)
	{
		*status = m_env(shell);
		return (1);
	}
	else if (strcmp(cmd->cmd, "exit") == 0)
	{
		*status = m_exit(shell, cmd);
		return (1);
	}
	return (0);
}
