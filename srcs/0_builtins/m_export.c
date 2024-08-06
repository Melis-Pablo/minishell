/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:18:55 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/06 19:20:03 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
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
}*/
#include <stdlib.h>
#include <string.h>

int init_parse_vars(const char *arg, const char **equal, const char **key_end, const char **value_start, const char **value_end)
{
	*equal = strchr(arg, '=');
	if (*equal == NULL) {
		*key_end = arg + strlen(arg);
		*value_start = NULL;
		*value_end = NULL;
	} else {
		*key_end = *equal - 1;
		*value_start = *equal + 1;
		*value_end = arg + strlen(arg);
	}

	if (*key_end == arg || (*equal != NULL && *value_start == *value_end))
		return (1);
	return (0);
}

int handle_no_equal(t_env *node, const char *key_start, const char *key_end, t_env *tmp)
{
	char *key;
	size_t key_len;

	key_len = key_end - key_start;
	key = strndup(key_start, key_len);
	if (!key)
		return (1);

	while (tmp->next)
		tmp = tmp->next;

	node->key = key;
	node->value = NULL;
	node->next = NULL;
	tmp->next = node;
	return (0);
}

int handle_with_equal(t_env *node, const char *key_start, const char *key_end, const char *value_start, const char *value_end, t_env *tmp)
{
	char	*key;
	char	*value;
	size_t	key_len;
	size_t	value_len;

	key_len = key_end - key_start + 1;
	value_len = value_end - value_start;

	key = strndup(key_start, key_len);
	value = strndup(value_start, value_len);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}

	while (tmp->next)
		tmp = tmp->next;

	node->key = key;
	node->value = value;
	node->next = NULL;
	tmp->next = node;
	return (0);
}

int parse_arg(t_env *node, char *arg, t_shell *shell)
{
	const char *equal;
	const char *key_end;
	const char *value_start;
	const char *value_end;
	const char *key_start;
	t_env *tmp;

	key_start = arg;
	tmp = shell->env;

	if (init_parse_vars(arg, &equal, &key_end, &value_start, &value_end))
		return (1);

	if (equal == NULL)
		return handle_no_equal(node, key_start, key_end, tmp);

	return handle_with_equal(node, key_start, key_end, value_start, value_end, tmp);
}


int	process_args(t_shell *shell, t_cmd *cmd, int *result)
{
	t_env	*node;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (ft_perror("malloc"));
		node->next = NULL;
		if (env_exist2(shell->env, cmd->args[i]) == 1)
		{
			free(node);
			i++;
			continue ;
		}
		if (parse_arg(node, cmd->args[i], shell) != 0)
		{
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
			free(node);
			*result = 1;
		}
		i++;
	}
	return (0);
}

int	m_export(t_shell *shell, t_cmd *cmd)
{
	int	result;

	result = 0;
	if (check_flag(cmd))
		return (1);
	if (process_args(shell, cmd, &result))
		return (1);
	sort(&shell->env);
	if (cmd->args[0] == NULL)
		print_env_list_export(shell->env);
	return (result);
}

/*
int	m_export(t_shell *shell, t_cmd *cmd)
{
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
			return (ft_perror("malloc"));
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
*/