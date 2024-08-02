/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 22:37:00 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "types.h"

// srcs/5.1_redirections/heredoc.c

int	process_all_heredocs(t_doc *heredocs, int heredoc_count);
// srcs/5.1_redirections/redirections.c
int		redirect_inputs(t_cmd *cmd);
int		redirect_outputs(t_cmd *cmd);
// srcs/6_execute/exec_utils.c
int		merge_args(t_cmd *cmd);
// srcs/6_execute/execution.c
int		exec_cmds(t_cmd *head);
// srcs/6_execute/find_exec.c
char	*find_command(char *cmd);

int		execute(t_shell *shell, char *line, int *status);
int		exec_pipe_cmd(t_shell *shell, t_cmd *cmd, t_pl *pl, int *status);
char	*get_exec_path(char *name, t_env *env);
int		exec_child(t_cmd *cmd, t_env *env);

int		check_input_redir(t_cmd *cmd, t_pl *pl);

const char	*get_env_nc(t_env *env, char *key);

void	*ft_memcpy(void *dst, const void *src, size_t n);

int	parse_env(char **envp, t_shell *shell);


char	*ft_strchr(const char *s, int chr);
char	**export_env(t_env *env);
int	handle_final_case(t_shell *shell, t_cmd *cmd, int *status, t_pl *pl);

int	execute_internal(t_shell *shell, t_cmd *cmd, int *status);


int	check_heredoc(t_cmd *cmd);
void	cleanup_heredocs(t_cmd *cmd);


#endif