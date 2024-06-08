/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/08 17:58:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
< should redirect input.
> should redirect output.
<< should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
>> should redirect output in append mode.
*/
/*
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
*/


t_cmd	*build_node(char **words)
{
	t_cmd	*new_cmd;
	int		i;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = strdup(words[0]);
	if (!new_cmd->cmd)
	{
		free(new_cmd);
		return (NULL);
	}
	i = 1;
	while (words[i] && words[i][0] == '-')
		i++;
	new_cmd->args = calloc(i, sizeof(char *));
	if (!new_cmd->args)
	{
		free(new_cmd->cmd);
		free(new_cmd);
		return (NULL);
	}
	i = 1;
	while (words[i] && words[i][0] == '-')
	{
		new_cmd->args[i - 1] = strdup(words[i]);
		if (!new_cmd->args[i - 1])
		{
			free_array(new_cmd->args);
			free(new_cmd->cmd);
			free(new_cmd);
			return (NULL);
		}
		i++;
	}
	new_cmd->args[i - 1] = NULL;
	new_cmd->flags = NULL;
	new_cmd->redirs = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*add_node_to_list(t_cmd *head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!head)
		return (new_cmd);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	return (head);
}

t_cmd	*build_cmd_lst(char *input)
{
	char	**strings;
	char	**words;
	int		i;
	t_cmd	*head;
	t_cmd	*new_cmd;

	head = NULL;
	new_cmd = NULL;
	strings = split_by_pipes(input);
	i = 0;
	while (strings[i] != NULL)
	{
		words = split_into_words(strings[i]);
		if (!words)
		{
			free_array(strings);
			return (NULL);
		}
		clean_quotes_in_array(words);
		new_cmd = build_node(words);
		head = add_node_to_list(head, new_cmd);
		free_array(words);
		i++;
	}
	free_array(strings);
	return (head);
}

void	print_nodes(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	while (tmp)
	{
		printf("cmd: %s\n", tmp->cmd);
		printf("args: ");
		print_str_array(tmp->args);
		printf("flags: ");
		print_str_array(tmp->flags);
		printf("redirs: ");
		i = 0;
		while (tmp->redirs[i].file)
		{
			printf("type: %d, file: %s\n", tmp->redirs[i].type, tmp->redirs[i].file);
			i++;
		}
		tmp = tmp->next;
	}
}

void free_redirs(t_redirection *redirs)
{
	int i;

	i = 0;
	while (redirs[i].file)
	{
		free(redirs[i].file);
		i++;
	}
	free(redirs);
}

void	free_cmd_lst(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_cmd	*next;
	int		i;

	tmp = cmds;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->cmd);
		free_array(tmp->args);
		free_array(tmp->flags);
		i = 0;
		while (tmp->redirs[i].file)
		{
			free_redirs(tmp->redirs);
			i++;
		}
		free(tmp->redirs);
		free(tmp);
		tmp = next;
	}
}
