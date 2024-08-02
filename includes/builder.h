/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:04:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 16:32:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

# include "minishell.h"
# include "types.h"

// srcs/builder.c
int		build_exec(char *input);
// srcs/1_split_tokens/split_tokens.c
char	**split_tokens(char *input);
// srcs/2_lexer/lexer_utils.c
t_token	*add_token(t_token *head, t_token *new_node);
t_token	*remove_token(t_token *node);
t_token	*inject_token(t_token *prev, t_token *new_node, t_token *next);
void	remove_empty_words(t_token *head);
void	set_types(t_token *head);
// srcs/2_lexer/lexer.c
t_token	*lexer(char **tokens);
// srcs/3_syntax_error/syntax_error.c
int		syntax_error(t_token *head);
int		check_inner_chars(char *word, char c);
// srcs/3_syntax_error/unclosed_quotes.c
int		unclosed_quotes(char *str);
// srcs/4_env_expand/OLD_envexpand.c
t_token	*env_expand(t_token *head);
// srcs/5_parser/parser_utils.c
t_redir	*get_infiles(t_token *head);
t_redir	*get_outfiles(t_token *head);
char	**get_args(t_token *head);
char	**get_flags(t_token *head);
char	*get_cmd(t_token *head);
// srcs/5_parser/parser.c
t_cmd	*parser(t_token *head);
t_redir	*add_redir(t_redir *head, t_redir *new_node);

void	load_env(t_shell *shell, char **envp);
t_cmd	*builder(char *input);

#endif