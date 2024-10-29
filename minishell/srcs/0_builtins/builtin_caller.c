/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:13:29 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/06 19:16:48 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_caller(t_shell *shell, t_cmd *cmd, int *status)
{
	if (strcmp(cmd->cmd, "pwd") == 0)
		*status = m_pwd(cmd);
	else if (strcmp(cmd->cmd, "echo") == 0)
		*status = m_echo(cmd);
	else if (strcmp(cmd->cmd, "cd") == 0)
		*status = m_cd(shell, cmd);
	else if (strcmp(cmd->cmd, "export") == 0)
		*status = m_export(shell, cmd);
	else if (strcmp(cmd->cmd, "unset") == 0)
		*status = m_unset(shell, cmd);
	else if (strcmp(cmd->cmd, "env") == 0)
		*status = m_env(shell);
	else if (strcmp(cmd->cmd, "exit") == 0)
		*status = m_exit(shell, cmd);
	else
		return (1);
	return (0);
}
