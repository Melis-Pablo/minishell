/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:29:25 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/03 15:23:51 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*add_token(t_token *head, t_token *new_node)
{
	t_token	*tmp;

	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	return (head);
}

t_token	*remove_token(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->word);
	free(node);
	return (tmp);
}

t_token	*inject_token(t_token *prev, t_token *new_node, t_token *next)
{
	new_node->next = next;
	new_node->prev = prev;
	prev->next = new_node;
	next->prev = new_node;
	return (next);
}

void	remove_empty_words(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->word[0] == '\0')
			tmp = remove_token(tmp);
		else
			tmp = tmp->next;
	}
}

void	set_types(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "<") == 0)
			tmp->type = INPUT;
		else if (ft_strcmp(tmp->word, ">") == 0)
			tmp->type = OUTPUT;
		else if (ft_strcmp(tmp->word, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->word, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->word, "|") == 0)
			tmp->type = PIPE;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}
