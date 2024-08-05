/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:49:49 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/05 17:40:04 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_redirs(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free_array(tmp->args);
		free_redirs(tmp->infiles);
		free_redirs(tmp->outfiles);
		free(tmp);
	}
}

