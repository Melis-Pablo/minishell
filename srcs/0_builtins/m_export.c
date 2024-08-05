/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/05 14:16:16 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// char *c = strchr(arg, '-');
	if (key_start == key_end || value_start == value_end )//|| c != NULL
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
		key = strndup(key_start, key_end - key_start + 1);
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

int	env_error_name(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			return (0);
		if (args[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	flag_checker(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	env_exists(t_env *env, char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int env_exist2(t_env *env, char *arg)
{	
	t_env *tmp;

	const char *equal = strchr(arg, '=');	// =
	const char *key_start = arg;		// key_start = arg
	const char *key_end = equal - 1;
	const char *value_start = equal + 1;	// value_start = equal + 1
	// const char *value_end = arg + strlen(arg);
	char *key = strndup(key_start, key_end - key_start + 1);
	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value_start);
			free(key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	return(0);
}

int	m_export(t_shell *shell, t_cmd *cmd)
{
	// t_env	*env_list;
	t_env	*node;
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (flag_checker(cmd->args))
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while (cmd->args[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
		{
			perror("malloc");
			return (1);
		}
		node->next = NULL;
		if (env_exist2(shell->env, cmd->args[i]) == 1)
		{
			result = 0;
			i++;
			free(node);
			continue ;
		}
		if (parse_arg(node, cmd->args[i], shell) != 0) //(cmd->flags[0] != NULL)
		{
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
			free(node);
			result = 1;
		}
		i++;
	}
	sort(&shell->env);
	if (cmd->args[0] == NULL)
		print_env_list_export(shell->env);
	return (result);
}
