/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/01 21:52:48 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}


int	m_exit(t_cmd *cmd)
{
	cmd->exit = 1;
	return (ft_atoi(cmd->args[0]));
}

/*
int	exit_cleanup(t_cmd *data)
{
	(void) data;
	//close fds()
	//close processes
	//free everything()
	//execute Commad handles
	//return exitcode
	return (0);
}

// while != exit in main loop

int	m_exit(t_cmd *cmd)
{
	cmd->exit = 0;
	return (cmd->exit);
}

// int	m_exit(char *cmd, t_data *data)
// {
// 	int	exitcode;

// 	exitcode = 0;
// 	(void) *data;
// 	//exit_cleanup();
// 	if (cmd != NULL)
// 		exitcode = atoi(cmd);
// 	if (exitcode < 0 && exitcode > 255)
// 		exitcode %= 256;
// 	//convertion error?
// 	_exit(exitcode);
// }
*/