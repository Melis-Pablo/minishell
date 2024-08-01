/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:13:29 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 18:12:07 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static int	check_builtin(t_shell *shell, t_cmd *cmd, int *status)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strncmp(g_builtins[i].name, cmd->name, 1000) == 0)
		{
			cmd->args++;
			cmd->argc--;
			*status = g_builtins[i].func(shell, cmd);
			cmd->args--;
			cmd->argc++;
			return (1);
		}
		i++;
	}
	return (0);
}
*/

int	builtins_caller(t_shell *shell, t_cmd *cmd, int *status)
{
	printf("command: <%s>\n\n", cmd->cmd);
	(void)shell;
	(void)status;

	// if (strcmp(cmd->cmd, "echo") == 0)
	// {
	// 	m_echo(cmd);
	// 	return (1);
	// }
	// else if (strcmp(cmd->cmd, "cd") == 0)
	// {
	// 	printf("ENTERED CD");
	// 	m_cd(cmd);
	// 	return (1);
	// }
	if (strcmp(cmd->cmd, "pwd") == 0)
	{
		m_pwd(cmd);
		return (1);
	}
	// else if (strcmp(cmd->cmd, "export") == 0)
	// {
	// 	m_export(cmd);
	// 	return (1);
	// }
	// else if (strcmp(cmd->cmd, "unset") == 0)
	// {
	// 	m_unset(cmd, cmd->args[0]);
	// 	return (1);
	// }
	// else if (strcmp(cmd->cmd, "env") == 0)
	// {
	// 	m_env(cmd);
	// 	return (1);
	// }
	// else if (strcmp(cmd->cmd, "exit") == 0)
	// {
	// 	m_exit(cmd);
	// 	return (1);
	// }
	return (0);
}
