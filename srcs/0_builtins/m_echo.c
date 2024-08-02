/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:46 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/02 19:01:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_line_check(char **flags)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (flags[j] == NULL || flags == NULL)
		return (0);
	while (flags[j][i])
	{
		if (flags[j][0] != '-')
			return (0);
		if (flags[j][i] == '-')
		{
			return (j);
		}
		if (flags[j][i] != 'n')
			return (0);
		i++;
	}
	// if (flags[0][i] == '\0')
	// 	return (0);
	return (j);
}

/*
m_echo():	echo command

Arguments:	t_cmd *cmd

Return:		void

How it works:
			1. starts index 0 arg
			2. newline std 1
			3. if first flag exist and newlinecheck 0(std case)
				4. newline = 0
*/
int	m_echo(t_cmd *cmd)
{
	int	start;
	int	newline;
	int	nl_flag;

	start = 0;
	newline = 1;
	nl_flag = new_line_check(cmd->flags);
	if (cmd->flags[0] != NULL && nl_flag != 0)
	{
		newline = 0;
		//print_str_array(cmd->flags + nl_flag);
		// merge_args(cmd);
	}
	if (cmd->args[start] != NULL)
	{
		while (cmd->args[start] != NULL)
		{
			printf("%s", cmd->args[start]);
			if (cmd->args[start + 1])
				printf(" ");
			start++;
		}
	}
	if (newline)
		printf("\n");
	return (0);
}

////////////////////////////////////////////////////////////////////////////////
//	Kevins /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
int	echo_builtin(t_shell *shell, const t_cmd *cmd)
{
	int	i;
	int	n_flag;

	(void)shell;
	i = 0;
	n_flag = 0;
	if (cmd->args[0] && ft_strncmp(cmd->args[0], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
*/
