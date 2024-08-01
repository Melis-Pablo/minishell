/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:46:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/01 17:55:18 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "types.h"

// srcs/utils/ft_split.c
char	**ft_split(char const *s, char c);
// srcs/utils/print.c
void	print_str_array(char **arr);
void	print_tokens(t_token *head);
void	print_redirs(t_redir *head);
void	print_cmds(t_cmd *head);
void	print_env_list(t_env *env);
void	print_env_list_export(t_env *env);
// srcs/utils/str_utils.c
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s1, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
// srcs/utils/str_utils2.c
char	*ft_strcat(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		array_len(char **arr);
// srcs/utils/utils.c 
int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
int		ft_is_space(char c);
void	ft_itoa(int n, char *str);

void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif