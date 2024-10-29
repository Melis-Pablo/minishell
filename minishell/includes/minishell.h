/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:14:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/29 18:27:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>             // printf & readline
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <unistd.h>            // write, getcwd, chdir, unlink, execve, dup,
								// dup2, pipe
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <readline/history.h>  // add_history
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset,
								// kill
# include <curses.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto,
								// tputs
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // perror
# include <fcntl.h>             // access, open, read, close
# include <termios.h>           // isatty, ttyname, ttyslot, tcsetattr,
								// tcgetattr
# include <sys/ioctl.h>         // ioctl
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // fork, wait, waitpid, wait3, wait4
# include <sys/wait.h>          // wait, waitpid, wait3, wait4

# include "builder.h"
# include "builtins.h"
# include "cleaners.h"
# include "execution.h"
# include "signal_handler.h"
# include "types.h"
# include "utils.h"

#endif