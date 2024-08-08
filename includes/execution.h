/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:10:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "types.h"

int			execute(t_shell *shell, char *line, int *status);
const char	*get_env_nc(t_env *env, char *key);
char		**export_env(t_env *env);
int			execute_internal(t_shell *shell, t_cmd *cmd, int *status);
int			redirect_outputs(t_cmd *cmd);
int			process_all_heredocs(t_doc *heredocs, int heredoc_count);
int			redirect_inputs(t_cmd *cmd);
int			exec_pipe_cmd(t_shell *shell, t_cmd *cmd, t_pl *pl, int *status);
char		*get_exec_path(char *name, t_env *env);
int			exec_child(t_cmd *cmd, t_env *env);
int			check_heredoc(t_cmd *cmd);
int			count_commands(t_cmd *cmd);

#endif