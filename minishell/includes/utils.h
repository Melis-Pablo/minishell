/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:46:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 14:09:44 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "types.h"

void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strcat(char *dst, const char *src);
int		ft_isalnum(int c);
int		ft_is_space(char c);
void	print_env_list_export(t_env *env);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		array_len(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_itoa(int n, char *str);
void	print_cmds(t_cmd *head);
void	print_redirs(t_redir *head);
void	print_str_array(char **arr);
void	print_tokens(t_token *head);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int chr);

#endif