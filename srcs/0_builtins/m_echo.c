/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:49:46 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/04 21:12:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	new_line_check(char **flags)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	j = 0;
// 	if (flags[j] == NULL || flags == NULL)
// 		return (0);
// 	while (flags[j][i])
// 	{
// 		if (flags[j][0] != '-')
// 			return (0);
// 		if (flags[j][i] == '-')
// 		{
// 			return (j);
// 		}
// 		if (flags[j][i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	// if (flags[0][i] == '\0')
// 	// 	return (0);
// 	return (j);
// }

// int	m_echo(t_cmd *cmd)
// {
// 	int	start;
// 	int	newline;
// 	int	nl_flag;

// 	start = 0;
// 	newline = 1;
// 	nl_flag = new_line_check(cmd->flags);
// 	if (cmd->flags[0] != NULL && nl_flag == 0)
// 	{
// 		newline = 0;
// 	}
// 	if (cmd->args[start] != NULL)
// 	{
// 		while (cmd->args[start] != NULL)
// 		{
// 			printf("%s", cmd->args[start]);
// 			if (cmd->args[start + 1])
// 				printf(" ");
// 			start++;
// 		}
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (0);
// }
