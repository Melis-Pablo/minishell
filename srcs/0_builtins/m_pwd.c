/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:57:40 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/04 15:28:21 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	m_pwd(t_cmd *cmd)
{
	char	*pwd;
	(void)	cmd;

	// ft_putendl_fd("pwd", STDOUT_FILENO);
	pwd = getcwd(0, 0);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
