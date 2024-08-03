/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:04:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/03 15:29:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

# include "minishell.h"
# include "types.h"

int		parse_env(char **envp, t_shell *shell);
char	**split_tokens(char *input);
t_token	*lexer(char **tokens);
int		syntax_error(t_token *head);
t_token	*env_expand(t_token *head);
t_cmd	*parser(t_token *head);
t_redir	*add_redir(t_redir *head, t_redir *new_node);
char	*get_cmd(t_token *head);
char	**get_args(t_token *head);
char	**get_flags(t_token *head);
t_redir	*get_infiles(t_token *head);
t_redir	*get_outfiles(t_token *head);
int		unclosed_quotes(char *str);
t_cmd	*builder(char *input);
int		check_inner_chars(char *word, char c);
t_token	*inject_token(t_token *prev, t_token *new_node, t_token *next);
t_token	*add_token(t_token *head, t_token *new_node);
void	set_types(t_token *head);
void	remove_empty_words(t_token *head);

#endif