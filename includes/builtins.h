/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:47:36 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/29 19:17:51 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	m_pwd(void);
int	m_exit(t_cmd *cmd);

// typedef int				(*t_builtin_func)(t_shell *shell, const t_cmd *cmd);

// typedef struct s_builtin
// {
// 	char			*name;
// 	t_builtin_func	func;
// }	t_builtin;

// static const t_builtin	g_builtins[] = {
// {"exit", exit_builtin},
// {"echo", echo_builtin},
// {"cd", cd_builtin},
// {"pwd", pwd_builtin},
// {"env", env_builtin},
// {"unset", unset_builtin},
// {"export", export_builtin},
// {0}
// };

#endif