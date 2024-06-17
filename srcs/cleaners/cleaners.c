/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:21 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/16 20:01:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
}

void	free_cmd(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free_array(tmp->args);
		free_array(tmp->flags);
		free_array(tmp->infiles);
		free_array(tmp->outfiles);
		free_array(tmp->heredocs);
		free_array(tmp->appendfiles);
		free(tmp);
	}
}

void	free_array_and_tokens(char **arr, t_token *head)
{
	free_array(arr);
	free_tokens(head);
}
