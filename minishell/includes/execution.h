/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 16:26:59 by grbuchne         ###   ########.fr       */
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
// int			merge_args(t_cmd *cmd);
int			exec_child(t_cmd *cmd, t_env *env);
int			check_heredoc(t_cmd *cmd);
char		*generate_filename(int count);
int			process_single_heredoc(const char *delimiter, char *filename);
ssize_t		finalize_read(ssize_t bytes_read, char *buffer, ssize_t *n);
ssize_t		read_and_store(int fd, char *buffer, ssize_t maxlen, ssize_t *n);
int			check_input(char *buffer, ssize_t maxlen);
ssize_t		ft_readlines(int fd, char *buffer, ssize_t maxlen);
void		cleanup_heredocs(t_cmd *cmd);
int			read_all_heredocs(t_doc *heredocs, int heredoc_count);
int			read_entire_file(int fd);
int			count_commands(t_cmd *cmd);
int			process_line(char *line, ssize_t *len,
				const char *delimiter, int tmp_fd);
int			read_and_write_heredoc(int tmp_fd, const char *delimiter);
int			free_pl_ret(void *pl, int ret);
#endif