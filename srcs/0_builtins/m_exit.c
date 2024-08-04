/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/04 14:34:59 by pmelis           ###   ########.fr       */
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
//if flags exist -12312 make it arg
// fix flags
int	m_exit(t_shell *shell, t_cmd *cmd)
{
	shell->exit = 1;
	if (cmd->args[0] && cmd->args[1])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	return (ft_atoi(cmd->args[0]));
}
