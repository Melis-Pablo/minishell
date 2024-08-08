/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:29:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 15:11:05 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *word, t_token_type type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = ft_strdup(word);
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	merge_redirects(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE && tmp->next)
		{
			free(tmp->word);
			if (tmp->next->type == WORD && !ck_in_ch(tmp->next->word, '|')
				&& !ck_in_ch(tmp->next->word, '>')
				&& !ck_in_ch(tmp->next->word, '<'))
			{
				tmp->word = ft_strdup(tmp->next->word);
				free(tmp->next->word);
				tmp->next->word = malloc(1 * sizeof(char));
				tmp->next->word[0] = '\0';
			}
			else
			{
				tmp->word = malloc(1 * sizeof(char));
				tmp->word[0] = '\0';
			}
		}
		tmp = tmp->next;
	}
}

void	complete_split(t_token *tmp, t_token_type type)
{
	free(tmp->word);
	tmp->word = ft_strdup("|");
	tmp->type = PIPE;
	if (type == INPUT)
		tmp = inject_token(tmp, create_token("<", INPUT), tmp->next);
	else if (type == OUTPUT)
		tmp = inject_token(tmp, create_token(">", OUTPUT), tmp->next);
	else if (type == APPEND)
		tmp = inject_token(tmp, create_token(">>", APPEND), tmp->next);
	else if (type == HEREDOC)
		tmp = inject_token(tmp, create_token("<<", HEREDOC), tmp->next);
}

void	split_piperedir(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "|<") == 0)
		{
			complete_split(tmp, INPUT);
		}
		else if (ft_strcmp(tmp->word, "|>") == 0)
		{
			complete_split(tmp, OUTPUT);
		}
		else if (ft_strcmp(tmp->word, "|>>") == 0)
		{
			complete_split(tmp, APPEND);
		}
		else if (ft_strcmp(tmp->word, "|<<") == 0)
		{
			complete_split(tmp, HEREDOC);
		}
		tmp = tmp->next;
	}
}

t_token	*lexer(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*new_node;

	i = 0;
	head = NULL;
	new_node = NULL;
	while (tokens[i])
	{
		new_node = create_token(tokens[i], WORD);
		if (!new_node)
		{
			free_tokens(head);
			return (NULL);
		}
		head = add_token(head, new_node);
		i++;
	}
	set_types(head);
	split_piperedir(head);
	merge_redirects(head);
	remove_empty_words(head);
	return (head);
}
