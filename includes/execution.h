/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/29 17:58:52 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "types.h"

// srcs/5.1_redirections/heredoc.c
int		process_all_heredocs(t_doc *heredocs, int heredoc_count);
// srcs/5.1_redirections/redirections.c
void	redirect_inputs(t_cmd *cmd);
void	redirect_outputs(t_cmd *cmd);
// srcs/6_execute/builtin_caller.c
int		builtins_caller(t_cmd *cmd);
// srcs/6_execute/exec_utils.c
char	**merge_args(t_cmd *cmd);
// srcs/6_execute/execution.c
int		exec_cmds(t_cmd *head);
// srcs/6_execute/find_exec.c
char	*find_command(char *cmd);

#endif