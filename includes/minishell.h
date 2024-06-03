/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 22:26:27 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 18:08:06 by pmelis           ###   ########.fr       */
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
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**flags;
	char			**infile;
	char			**outfile;
	char			**delimiter;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			**append;
}					t_cmd;

/////////////////////////
// Function prototypes //
/////////////////////////

//Cleaners.c
void			free_array(char **array);
void			free_cmds(t_cmd *cmds);

//Tools.c
char			*ft_strndup(const char *s, size_t n);

//zprint.c
void			print_str_array(char **arr);
void			print_cmds_list(t_cmd *head);

//Split_into_words.c
char			**split_into_words(char *str_block);

/////////////////////////Need Cleaning

//Split_by_pipes.c
char			**split_by_pipes(char *input);

//Cmd_builder.c
t_cmd			*cmd_builder(char *input);
void			print_cmds_list(t_cmd *head);

#endif
