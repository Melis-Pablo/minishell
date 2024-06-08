/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:26:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/08 17:50:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//////////////////////////
// Include dependencies //
//////////////////////////
// Comments define which functions are allowed to be used in the project
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
	REDIR_INPUT = 1,	// <
	REDIR_OUTPUT = 2,	// >
	REDIR_HEREDOC = 3,	// <<
	REDIR_APPEND = 4,	// >>
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type	type;	// Type of redirection
	char				*file;	// File associated with redirection
}						t_redirection;

typedef struct s_cmd
{
	char			*cmd;		// Command name
	char			**args;		// Arguments for the command
	char			**flags;	// Flags for the command
	t_redirection	*redirs;	// Array of redirections
	struct s_cmd	*next;		// Pointer to the next command in the pipeline
}					t_cmd;

/////////////////////////
// Function prototypes //
/////////////////////////

//Cleaners.c
void			free_array(char **array);
void			free_cmd_lst(t_cmd *cmds);

//Tools.c
char			*ft_strndup(const char *s, size_t n);

//print.c
void			print_str_array(char **arr);
void			print_cmds_list(t_cmd *head);

//Split_into_words.c
char			**split_into_words(char *str_block);

//Split_by_pipes.c
char			**split_by_pipes(char *input);

char			*ft_clean_quotes(char *word);
void			clean_quotes_in_array(char **array);

t_cmd			*build_cmd_lst(char *input);
void			print_nodes(t_cmd *head);
void			free_cmd_lst(t_cmd *cmds);

#endif
