/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:47:05 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/23 05:50:26 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*get_infiles(t_token *head)
{
	t_redir	*infiles;
	t_token	*tmp;
	t_redir	*new_node;

	infiles = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			new_node = (t_redir *)malloc(sizeof(t_redir));
			new_node->file = ft_strdup(tmp->word);
			new_node->type = tmp->type;
			new_node->next = NULL;
			infiles = add_redir(infiles, new_node);
		}
		tmp = tmp->next;
	}
	return (infiles);
}

t_redir	*get_outfiles(t_token *head)
{
	t_redir	*outfiles;
	t_token	*tmp;
	t_redir	*new_node;

	outfiles = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			new_node = (t_redir *)malloc(sizeof(t_redir));
			new_node->file = ft_strdup(tmp->word);
			new_node->type = tmp->type;
			new_node->next = NULL;
			outfiles = add_redir(outfiles, new_node);
		}
		tmp = tmp->next;
	}
	return (outfiles);
}

char	**get_args(t_token *head)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	args = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && !(strncmp(tmp->word, "-", 1) == 0))
			i++;
		tmp = tmp->next;
	}
	args = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			head = head->next;
			break ;
		}
		head = head->next;
	}
	while (head && head->type != PIPE)
	{
		if (head->type == WORD && !(strncmp(head->word, "-", 1) == 0))
		{
			args[i] = ft_strdup(head->word);
			i++;
		}
		head = head->next;
	}
	args[i] = NULL;
	return (args);
}

char	**get_flags(t_token *head)
{
	char	**flags;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = head;
	flags = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && strncmp(tmp->word, "-", 1) == 0)
			i++;
		tmp = tmp->next;
	}
	flags = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			head = head->next;
			break ;
		}
		head = head->next;
	}
	while (head && head->type != PIPE)
	{
		if (head->type == WORD && strncmp(head->word, "-", 1) == 0)
		{
			flags[i] = ft_strdup(head->word);
			i++;
		}
		head = head->next;
	}
	flags[i] = NULL;
	return (flags);
}

char	*get_cmd(t_token *head)
{
	char	*cmd;

	cmd = NULL;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			cmd = ft_strdup(head->word);
			break ;
		}
		head = head->next;
	}
	return (cmd);
}
