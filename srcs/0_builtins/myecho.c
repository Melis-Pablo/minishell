/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myecho.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:23:57 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/04 21:07:24 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	new_line_check(char **flags)
// {
// 	int	i;
// 	int final_ret;

// 	i = 0;
// 	if (flags[i] == NULL || flags == NULL)
// 		return (0);
// 	while (flags[i])
// 	{
// 		if (ft_strcmp(flags[i], "-n") == 0)
// 		{
// 			final_ret = 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	while (flags[i])
// }

// int	m_echo(t_cmd *cmd)
// {
// 	int	start;
// 	int	newline;
// 	int	nl_flag;

// 	start = 0;
// 	newline = 1;
// 	t_cmd *tmp = cmd;
// 	merge_args(tmp);
// 	nl_flag = new_line_check(tmp->args);
// 	if (nl_flag == 0)
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

// int	check_echo_n_flags(char **args, int *i)
// {
// 	int n_flag;
// 	int j;

// 	n_flag = 0;
// 	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
// 	{
// 		j = 2;
// 		while (args[*i][j] == 'n')
// 			j++;
// 		if (args[*i][j] == '\0')
// 		{
// 			(*i)++;
// 			n_flag = 1;
// 		}
// 		else
// 			break ;
// 	}
// 	return (n_flag);
// }

// int m_echo(t_cmd *cmd)
// {
// 	int i;
// 	int n_flag;

// 	i = 1;
// 	t_cmd *tmp = cmd;
// 	merge_args(tmp);
// 	n_flag = check_echo_n_flags(tmp->args, &i);
// 	while (tmp->args[i])
// 	{
// 		ft_putstr_fd(tmp->args[i], STDOUT_FILENO);
// 		if (tmp->args[i + 1])
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (!n_flag)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	return (0);
// }