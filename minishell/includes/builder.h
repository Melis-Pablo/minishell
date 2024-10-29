/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:04:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 19:34:32 by pmelis           ###   ########.fr       */
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
t_token	*env_expand(t_token *head, t_shell *shell);
t_cmd	*parser(t_token *head);
t_redir	*add_redir(t_redir *head, t_redir *new_node);
char	*get_cmd(t_token *head);
char	**get_args(t_token *head);
t_redir	*get_infiles(t_token *head);
t_redir	*get_outfiles(t_token *head);
int		unclosed_quotes(char *str);
t_cmd	*builder(char *input, t_shell *shell);
int		ck_in_ch(char *word, char c);
t_token	*inject_token(t_token *prev, t_token *new_node, t_token *next);
t_token	*add_token(t_token *head, t_token *new_node);
void	set_types(t_token *head);
void	remove_empty_words(t_token *head);
char	*get_var_name(char *start, char *end);
char	*var_to_value(char *word, char *start, char *end, char *var_value);
char	*expand_exit_status(char *word, char *start, char *end, t_shell *shell);
char	*get_var_value(char *var_name, t_env *env);
char	*expand_env_variables(char *word, t_shell *shell);
char	*get_token(char **input);
int		check_delimiter(char *input, int *in_quote, char *quote);

#endif