/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:47:36 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/03 14:18:13 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		m_pwd(t_cmd *cmd);
int		m_exit(t_shell *shell, t_cmd *cmd);
int		m_env(t_shell *shell);
int		m_export(t_shell *shell, t_cmd *cmd);
int		m_unset(t_shell *shell, t_cmd *cmd);
int		m_cd(t_shell *shell, t_cmd *cmd);
int		m_echo(t_cmd *cmd);
int		builtins_caller(t_shell *shell, t_cmd *cmd, int *status);

#endif