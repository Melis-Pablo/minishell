/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:59:33 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:20:03 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//////////////////////////
// Include dependencies //
//////////////////////////
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <curses.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto,
								//tputs
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // perror
# include <fcntl.h>             // access, open, read, close
# include <readline/history.h>  // add_history
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset,
								//kill
# include <stdio.h>             // printf
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/ioctl.h>         // ioctl
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // fork, wait, waitpid, wait3, wait4
# include <termios.h>           // isatty, ttyname, ttyslot, tcsetattr,
								//tcgetattr
# include <unistd.h>            // write, getcwd, chdir, unlink, execve, dup,
								//dup2, pipe

//////////////////////////
//   Global Variables   //
//////////////////////////
extern int	g_signal_status;

//////////////////////////
// Data structure types //
//////////////////////////
typedef enum e_redirection_type
{
	NO_REDIRECTION = 0, // cmd, args, flags
	REDIR_INPUT = 1,	// <
	REDIR_OUTPUT = 2,	// >
	REDIR_HEREDOC = 3,	// <<
	REDIR_APPEND = 4,	// >>
}	t_redirection_type;

typedef struct s_lexer
{
	char				*word;
	t_redirection_type	type;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_cmd
{
	t_lexer			*lexer;		// List of words and redirections
	struct s_cmd	*next;		// Pointer to next command in the pipeline
}					t_cmd;

/////////////////////////
// Function prototypes //
/////////////////////////


void	free_array(char **arr);
void	free_cmd_lst(t_cmd *cmds);
void	free_lexer_list(t_lexer *head);


void	fill_types(t_lexer *head);
t_lexer	*add_to_list_lexer(t_lexer *head, t_lexer *new_node);
void	empty_redir_words(t_lexer *head);
t_lexer	*take_out_node(t_lexer *node);
void	remove_emptys(t_lexer *head);
t_lexer	*lexer(char **words);


void	clean_redir_symbols(t_lexer *head);
int		is_input_redirection(char *word);
int		is_output_redirection(char *word);
int		is_heredoc_redirection(char *word);
int		is_append_redirection(char *word);


t_cmd	*add_node_to_list(t_cmd **head, t_cmd *new_cmd);
t_cmd	*build_node(char **words);
t_cmd	*process_words(char **words, t_cmd *head);
t_cmd	*process_string(char *str, t_cmd *head);
t_cmd	*build_struct(char *input);


char	*get_var_name(char *start, char *end);
char	*var_to_value(char *word, char *start, char *end, char *var_value);
char	*expand_exit_status(char *word, char *start, char *end);
char	*expand_env_variables(char *word);


int		check_quotes_and_pipes(char *input, int *in_quote, char *quote);
int		count_pipes(char *input);
int		count_until_pipe(char *input);
char	*copy_until_pipe(char *start);
char	**split_by_pipes(char *input);


int		count_words(char *str);
char	*get_word(char **str);
char	**split_into_words(char *str);


int		check_unclosed_quote(char *str);
int		check_backslash(char *str);
int		string_error(char *str);


int		check_parentheses(char *word);
int		check_and(char *word);
int		check_wildcard(char *word);
int		check_backslash_word(char *word);
int		check_semicolon(char *word);


int		check_or(char *word);
void	word_error(char *word, int error_code);
int		check_invalid_char(char *word);


void	print_str_array(char **arr);
void	print_strings_and_words(char *input);
void	print_lexer_list(t_lexer *head);
void	print_cmd_lst(t_cmd *head);
void	print_lexed(char *input);


int		is_space(char c);
void	reverse_str(char *str, int len);
void	ft_itoa(int n, char *str);
char	*ft_clean_quotes(char *word);


char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);


char	*ft_strdup(const char *s);
int		ft_isalnum(int c);
void	my_execution(t_cmd *head);

#endif
