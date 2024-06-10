/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:26:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/10 21:06:33 by pmelis           ###   ########.fr       */
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
	NO_REDIRECTION = 0,
	REDIR_INPUT = 1,	// <
	REDIR_OUTPUT = 2,	// >
	REDIR_HEREDOC = 3,	// <<
	REDIR_APPEND = 4,	// >>
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;	// Type of redirection
	char					*file;	// File associated with redirection
	struct s_redirection	*next;	// Pointer to next redirection in the list
}						t_redirection;

typedef struct s_lexer
{
	char			*word;
	int				type;
	struct s_lexer	*prev;
	struct s_lexer	*next;

}	t_lexer;

typedef struct s_cmd
{
	char			*cmd;		// Command name
	char			**args;		// Arguments for the command
	char			**flags;	// Flags for the command
	t_redirection	*redirs;	// Array of redirections
	struct s_cmd	*next;		// Pointer to next command in the pipeline
	struct s_cmd	*prev;		// Pointer to previous command in the pipeline
}					t_cmd;

/////////////////////////
// Function prototypes //
/////////////////////////

//	cleanup/cleaners.c
void	free_array(char **arr);
void	free_redirs(t_redirection *redirs);
void	free_cmd_lst(t_cmd *cmds);

//	parsing/cmd_lst.c
t_cmd	*build_node(char **words);
t_cmd	*add_node_to_list(t_cmd *head, t_cmd *new_cmd);
t_cmd	*build_cmd_lst(char *input);

//	parsing/env_var.c
char	*get_var_name(char *start, char *end);
char	*var_to_value(char *word, char *start, char *end, char *var_value);
char	*expand_exit_status(char *word, char *start, char *end);
char	*expand_env_variables(char *word);

//	parsing/split_by_pipes.c
int		check_quotes_and_pipes(char *input, int *in_quote, char *quote);
int		count_pipes(char *input);
int		count_until_pipe(char *input);
char	*copy_until_pipe(char *start);
char	**split_by_pipes(char *input);

//	parsing/split_into_words.c
int		count_words(char *str);
char	*get_word(char **str);
char	**split_into_words(char *str);

//	parsing/str_error.c
int		check_unclosed_quote(char *str);
int		check_backslash(char *str);
int		string_error(char *str);

//	parsing/word_error.c
int		check_single_special(char *word, char c);
int		check_double_special(char *word, char c1, char c2);
int		check_or(char *word);
void	word_error(char *word, int error_code);
int		check_invalid_char(char *word);

//	parsing/word_error_checks.c
int		check_parentheses(char *word);
int		check_and(char *word);
int		check_wildcard(char *word);
int		check_backslash_word(char *word);
int		check_semicolon(char *word);

//	utils/print.c
void	print_str_array(char **arr);
void	print_strings_and_words(char *input);
void	print_nodes(t_cmd *head);

//	utils/utils.c
int		is_space(char c);
void	reverse_str(char *str, int len);
void	ft_itoa(int n, char *str);
char	*ft_clean_quotes(char *word);
void	clean_quotes_in_array(char **array);

//	utils/utils_2.c
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);




/////

char	**build_array(char *input);
void	print_lexed(char *input);
char	*ft_strdup(const char *s);

#endif
