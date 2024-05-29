/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:26:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/29 12:35:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// Data structures
typedef enum s_token_type
{
	NONE = 0,
	PIPE = 1,
	GREATER = 2,
	LESS = 3,
	GREATER_GREATER = 4,
	LESS_LESS = 5,
}	t_token_type;

typedef struct s_lexer
{
	char			*str;
	t_token_type	token;
	int				index;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**flags;
	char			**infile;
	char			**outfile;
	char			*delimiter;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			**append;
}					t_cmd;

// Function prototypes
char	**string_blocks(char *input);
char	**split_string(char *input);

#endif
