/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:59:33 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 17:23:10 by pmelis           ###   ########.fr       */
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

//////////////////////////
//		cleaners		//
//////////////////////////
// srcs/cleaners/cleaners.c
void	free_array(char **arr);
void	free_lexer_list(t_lexer *head);
void	free_cmd_lst(t_cmd *cmds);

//////////////////////
//		lexer		//
//////////////////////
// srcs/lexer/splits/split_pipeline.c
char	**split_pipeline(char *input);
// srcs/lexer/splits/split_tokens.c
char	**split_tokens(char *pipe);
// srcs/lexer/lexer_types.c
void	fill_types(t_lexer *head);
// srcs/lexer/lexer.c
t_lexer	*lexer(char **tokens);

//////////////////////
//		parser		//
//////////////////////
// srcs/parser/token_errors/invalid_tokens.c
int		check_parentheses(char *word);
int		check_and(char *word);
int		check_wildcard(char *word);
int		check_backslash_word(char *word);
int		check_semicolon(char *word);

int		check_invalid_char(char *word);
int		expand_all(t_cmd *head_cmd);
int		unclosed_quotes(char *str);

// srcs/parser/token_errors/error_check.c
int		error_check(t_cmd *head_cmd);

// srcs/parser/expand_env.c
char	*ft_clean_quotes(char *word);

// srcs/parser/build_cmd_lst.c
t_cmd	*build_cmds(char *input);

//////////////////////
//	   redirects  	//
//////////////////////

//////////////////////
//		utils		//
//////////////////////
// srcs/utils/print.c
void	print_str_array(char **arr);
void	print_pipes_and_tokens(char *input);
void	print_lexer_list(t_lexer *head);
void	print_cmd_lst(t_cmd *head);
void	print_lexed(char *input);

// srcs/utils/str_utils.c
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strcat(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);

// srcs/utils/utils.c
int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
int		ft_is_space(char c);
void	ft_reverse_str(char *str, int len);
void	ft_itoa(int n, char *str);

#endif
