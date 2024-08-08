/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:25 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/05 18:57:29 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

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

int	m_exit(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	shell->exit = 1;
	if (cmd->args[0] && cmd->args[1])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	if (cmd->args[0])
	{
		while (cmd->args[0][i])
		{
			if (ft_isalpha(cmd->args[0][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n",
					cmd->args[0]);
				return (1);
			}
			i++;
		}
	}
	return (ft_atoi(cmd->args[0]));
}
