/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:47:03 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/05 17:42:10 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*add_node(t_cmd *head, t_cmd *new_node)
{
	t_cmd	*last;

	if (!head)
		return (new_node);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (head);
}

t_redir	*add_redir(t_redir *head, t_redir *new_node)
{
	t_redir	*last;

	if (!head)
		return (new_node);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (head);
}

t_cmd	*create_node(t_token *head)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = get_cmd(head);
	new_node->args = get_args(head);
	new_node->infiles = get_infiles(head);
	new_node->outfiles = get_outfiles(head);
	new_node->heredocs = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	print_single_node(t_cmd *node)
{
	ft_putstr_fd("cmd: ", 1);
	ft_putendl_fd(node->cmd, 1);
	ft_putstr_fd("args: ", 1);
	print_str_array(node->args);
	ft_putstr_fd("infiles: ", 1);
	print_redirs(node->infiles);
	ft_putstr_fd("outfiles: ", 1);
	print_redirs(node->outfiles);
	printf("\n");
}

t_cmd	*parser(t_token *head)
{
	t_cmd	*cmds;
	t_token	*tmp;
	t_cmd	*new_node;

	cmds = NULL;
	tmp = head;
	new_node = NULL;
	while (tmp)
	{
		new_node = create_node(head);
		cmds = add_node(cmds, new_node);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (!tmp)
			break ;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		head = tmp;
	}
	return (cmds);
}
