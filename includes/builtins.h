/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:47:36 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 20:30:32 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/// m_pwd /////////
int			m_pwd(t_cmd *cmd);
/// m_exit /////////
int			m_exit(t_shell *shell, t_cmd *cmd);
int			ft_isalpha(int c);
int			ft_atoi(const char *str);
/// m_env /////////
int			m_env(t_shell *shell);
/// m_export /////////
int			m_export(t_shell *shell, t_cmd *cmd);
void		sort(t_env **env);
void		lst_swap_next(t_env **env);
int			get_env_length(t_env *env);
int			parse_arg(t_env *node, char *arg, t_shell *shell);
t_envarg	*init_envarg2(t_envarg *envarg, char *arg);
/// m_unset /////////
int			m_unset(t_shell *shell, t_cmd *cmd);
int			remove_variable(t_shell *shell, char *var);
/// m_cd /////////
int			m_cd(t_shell *shell, t_cmd *cmd);
int			get_home(t_env **env);
int			get_parent_directory_index(char *str);
int			get_up(t_shell *shell);
/// m_echo /////////
int			m_echo(t_cmd *cmd);

/// m_builtins_caller /////////
int			builtins_caller(t_shell *shell, t_cmd *cmd, int *status);

/// m_builtin_utils /////////
int			env_error_name(char *args);
int			flag_checker(char **args);
int			env_exists(t_env *env, char *key);
void		set_value_null(t_env *tmp);
void		set_value(t_env *tmp, t_envarg envarg);

/// m_builtin_utils2 /////////

int			ft_perror(char *str, int i);
int			update_pwd3(t_env *env, const char *new_pwd);
int			process_pwd_entry(t_env *env);
int			get_up(t_shell *shell);

/// m_builtin_utils3 /////////

char		*find_home_path(t_env *env);
int			update_pwd2(t_env *env, char *new_pwd);
char		*change_to_home(const char *home_path);
int			get_home(t_env **env);
int			get_parent_directory_index(char *str);

/// m_builtin_utils4 /////////

int			get_env_length(t_env *env);
void		lst_swap_next(t_env **env);
void		sort(t_env **env);
int			check_flag(t_cmd *cmd);

/// m_builtin_utils5 /////////
t_envarg	*init_envarg(t_envarg *envarg, char *arg);
int			env_exist2(t_env *env, char *arg);
void		add_with_value(t_env *node, char *key, char *v_s, t_env *env);

#endif