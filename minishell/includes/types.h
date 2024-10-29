/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:39:59 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/09 13:13:17 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

# define PROMPT "\033[32mminishell> \033[0m"

typedef enum e_token_type
{
	WORD = 0,
	INPUT = 1,
	OUTPUT = 2,
	HEREDOC = 3,
	APPEND = 4,
	PIPE = 5,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_envarg
{
	char	*equal;
	char	*key_start;
	char	*key_end;
	char	*value_start;
	char	*key;
	char	*value_end;
}	t_envarg;

typedef struct s_shell
{
	int		first_run;
	int		last_status;
	int		exit;
	int		envc;
	t_env	*env;
}	t_shell;

typedef struct s_redir
{
	char			*file;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_doc
{
	char	*filename;
	char	*delimiter;
}	t_doc;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	// char			**flags;
	t_doc			*heredocs;
	int				heredoc_count;
	struct s_redir	*infiles;
	struct s_redir	*outfiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pl
{
	int		pipe_fd[2];
	int		fd_out;
	int		fd_in;
}	t_pl;

#endif