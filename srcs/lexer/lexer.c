/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:48:49 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:32:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_types(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_input_redirection(tmp->word))
			tmp->type = REDIR_INPUT;
		else if (is_output_redirection(tmp->word))
			tmp->type = REDIR_OUTPUT;
		else if (is_heredoc_redirection(tmp->word))
			tmp->type = REDIR_HEREDOC;
		else if (is_append_redirection(tmp->word))
			tmp->type = REDIR_APPEND;
		else
			tmp->type = NO_REDIRECTION;
		tmp = tmp->next;
	}
}

t_lexer	*add_to_list_lexer(t_lexer *head, t_lexer *new_node)
{
	t_lexer	*tmp;

	if (!head)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		return (new_node);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (head);
}

void	empty_redir_words(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if ((tmp->type == REDIR_INPUT && ft_strcmp(tmp->word, "<") == 0)
			|| (tmp->type == REDIR_OUTPUT && ft_strcmp(tmp->word, ">") == 0)
			|| (tmp->type == REDIR_HEREDOC && ft_strcmp(tmp->word, "<<") == 0)
			|| (tmp->type == REDIR_APPEND && ft_strcmp(tmp->word, ">>") == 0))
		{
			free(tmp->word);
			if (tmp->next->type == NO_REDIRECTION)
			{
				tmp->word = ft_strdup(tmp->next->word);
				free(tmp->next->word);
				tmp->next->word = malloc(1 * sizeof(char));
				tmp->next->word[0] = '\0';
			}
			else
			{
				perror("Syntax error near unexpected redirection");
				break ;
			}
		}
		if (tmp->type == NO_REDIRECTION)
			tmp->word = ft_clean_quotes(tmp->word);
		tmp = tmp->next;
	}
}

t_lexer	*take_out_node(t_lexer *node)
{
	t_lexer	*tmp;

	tmp = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->word);
	free(node);
	return (tmp);
}

void	remove_emptys(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == NO_REDIRECTION && tmp->word[0] == '\0'
			&& tmp->next != NULL)
		{
			tmp = take_out_node(tmp);
		}
		tmp = tmp->next;
	}
}

t_lexer	*lexer(char **words)
{
	int		i;
	t_lexer	*head;
	t_lexer	*new_node;

	i = 0;
	head = NULL;
	while (words[i])
	{
		new_node = malloc(sizeof(t_lexer));
		if (!new_node)
			return (NULL);
		new_node->word = ft_strdup(words[i]);
		new_node->type = NO_REDIRECTION;
		new_node->prev = NULL;
		head = add_to_list_lexer(head, new_node);
		i++;
	}
	fill_types(head);
	empty_redir_words(head);
	clean_redir_symbols(head);
	remove_emptys(head);
	return (head);
}
