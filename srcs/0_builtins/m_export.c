/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/02 21:49:49 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//still to-do
//ascii order!!!
#include "../../includes/minishell.h"

// void add_env_node_back(t_env **envp, char *key, char *value)
// {
// 	t_env *node;
// 	t_env *i;

// 	if (!key || !envp || !value)
// 	{
// 		return;
// 	}

// 	node = malloc(sizeof(t_env));
// 	if (node == NULL)
// 	{
// 		perror("d;s");
// 		exit(1);
// 	}
// 	node->key = strdup(key);
// 	node->value = strdup(value);
// 	node->next = NULL;

// 	if (*envp == NULL)
// 	{
// 		*envp = node;
// 	}
// 	else
// 	{
// 		i = *envp;
// 		while (i && i->next != NULL)
// 		{
// 			i = i->next;
// 		}
// 		if (i)
// 		{
// 			i->next = node;
// 		}
// 	}
// }

// int parse_env(char **envp, t_env **env)
// {
// 	int i;
// 	char *entry;
// 	char *key;
// 	char *value;
// 	char *equal_sign;

// 	if (!env || !envp)
// 	{
// 		return (1);
// 	}

// 	i = 0;
// 	key = NULL;
// 	equal_sign = NULL;
// 	value = NULL;
// 	while (envp[i] != NULL)
// 	{
// 		entry = strdup(envp[i]);
// 		equal_sign = strchr(entry, '=');
// 		if (!equal_sign)
// 		{
// 			return (1);
// 		}
// 		else
// 		{
// 			*equal_sign = '\0';
// 		}
// 		key = entry;
// 		value = equal_sign + 1;
// 		add_env_node_back(env, key, value);
// 		i++;
// 	}
// 	return (0);
// }

int	parse_arg(t_env *node, char *arg, t_shell *shell)
{
	const char *equal = strchr(arg, '=');	// =
	const char *key_start = arg;		// key_start = arg
	const char *key_end = equal - 1;	// key_end = equal - 1
	const char *value_start = equal + 1;	// value_start = equal + 1
	const char *value_end = arg + strlen(arg);	// value_end = arg + strlen(arg)
	char *key = NULL;
	char *value = NULL;
	t_env *tmp;

	tmp = shell->env;
	if (key_start == key_end || value_start == value_end)
		return (1);
	if (strchr(arg, '=') == NULL)
	{
		key = strndup(key_start, key_end - key_start);
		while (tmp->next)
			tmp = tmp->next;
		node->key = key;
		node->value = NULL;
		node->next = NULL;
		tmp->next = node;
	}
	else
	{
		key = strndup(key_start, key_end - key_start);
		value = strndup(value_start, value_end - value_start);
		while (tmp->next)
			tmp = tmp->next;
		node->key = key;
		node->value = value;
		node->next = NULL;
		tmp->next = node;
	}
	return (0);
}

int get_env_length(t_env *env) {
	int i = 0;

	while (env) {
		env = env->next;
		i++;
	}
	return (i);
}

void lst_swap_next(t_env **env) {
	t_env *tmp;

	if (!env || !*env || !(*env)->next) {
		return;
	}
	tmp = (*env)->next;
	(*env)->next = (*env)->next->next;
	tmp->next = *env;
	(*env) = tmp;
}

void sort(t_env **env)
{
	t_env **a;
	int i;
	int len;

	if (!env || !*env || !(*env)->next) {
		return;
	}

	len = get_env_length(*env);
	while(len > 1)
	{
		a = env;
		i = 0;
		while(a != NULL && (*a)->next != NULL && i < len)
		{
			if (strcmp((*a)->key, (*a)->next->key) > 0) {
				lst_swap_next(a);
			}
			a = &(*a)->next;
			i++;
		}
		len--;
	}
}

int	m_export(t_shell *shell, t_cmd *cmd)
{
	// t_env	*env_list;
	t_env	*node;
	int		result;
	int		i;

	result = 0;
	i = 0;
	while (cmd->args[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
		{
			perror("malloc");
			return (1);
		}
		node->next = NULL;
		if (parse_arg(node, cmd->args[i], shell) != 0)
		{
			printf("parsing der Hurensohn wieder :(");
			result = 1;
		}
		i++;
	}
	//printf("key=%s | value=%s", node->key, node->value);
	// free(node);
	//print_env_list(env_list);
	sort(&shell->env);
	if (cmd->args[0] == NULL)
		print_env_list_export(shell->env);
	return (result);
}
