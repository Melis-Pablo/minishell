/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:45:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/03 15:31:30 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_node_back(t_env **envp, char *key, char *value)
{
	t_env	*node;
	t_env	*i;

	if (!key || !envp || !value)
	{
		return ;
	}
	node = malloc(sizeof(t_env));
	if (node == NULL)
	{
		perror("d;s");
		exit(1);
	}
	node->key = strdup(key);
	node->value = strdup(value);
	node->next = NULL;
	if (*envp == NULL)
	{
		*envp = node;
	}
	else
	{
		i = *envp;
		while (i && i->next != NULL)
		{
			i = i->next;
		}
		if (i)
		{
			i->next = node;
		}
	}
}

int	parse_env(char **envp, t_shell *shell)
{
	int		i;
	char	*entry;
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!shell || !envp)
	{
		return (1);
	}
	i = 0;
	key = NULL;
	equal_sign = NULL;
	value = NULL;
	shell->envc = 0;
	while (envp[i] != NULL)
	{
		entry = strdup(envp[i]);
		if (!entry)
            return (1);
		equal_sign = strchr(entry, '=');
		if (!equal_sign)
		{
            free(entry);
			return (1);
		}
		else
		{
			*equal_sign = '\0';
		}
		key = entry;
		value = equal_sign + 1;
		add_env_node_back(&shell->env, key, value);
        free(entry);
        shell->envc++;
		i++;
	}
	return (0);
}
