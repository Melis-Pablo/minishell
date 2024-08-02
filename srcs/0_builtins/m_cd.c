/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/02 20:10:03 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_home(t_env **env)
{
	t_env	*i;
	char	*path;
	t_env	*k;

	i = *env;
	while (i != NULL)
	{
		if (strcmp(i->key, "HOME") == 0)
		{
			if (chdir(i->value) == 0)
			{
				path = getcwd(NULL, 0);
				if (path)
				{
					k = *env;
					while (k != NULL)
					{
						if (strcmp(k->key, "PWD") == 0)
						{
							free(k->value);
							k->value = strdup(path);
							free(path);
							return (0);
						}
						k = k->next;
					}
					free(path);
				}
			}
			return (1);  
		}
		i = i->next;
	}
	return (1);
}

int	get_parent_directory_index(char *str)
{
	int	i;

	i = strlen(str) - 1;
	while (i > 0 && str[i] != '/')
		i--;
	return (i);
}

int	get_up(t_shell *shell)
{
	t_env	*env;
	char	*new_pwd;
	int		index;

	env = shell->env;
	while (env != NULL)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			printf("env->value: %s\n", env->value);
			index = get_parent_directory_index(env->value);
			printf("index: %d\n", index);
			if (index > 0)
			{
				new_pwd = strndup(env->value, index);
				printf("new_pwd: %s\n", new_pwd);
				if (new_pwd)
				{
					free(env->value);
					env->value = new_pwd;
					chdir(env->value);
					return (0);
				}
			}
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	m_cd(t_shell *shell, t_cmd *cmd)
{
	char	*old_pwd;
	char	*new_pwd;
	t_env	*env;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		return (1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		if (get_home(&shell->env) != 0)
			fprintf(stderr, "Failed to change to HOME directory\n");
	}
	else if (strcmp(cmd->args[0], "~") == 0)
	{
		if (get_home(&shell->env) != 0)
			fprintf(stderr, "Failed to change to HOME directory\n");
	}
	else if (strcmp(cmd->args[0], "..") == 0)
	{
		if (get_up(shell) != 0)
			fprintf(stderr, "Failed to change to parent directory\n");
	}
	else if (chdir(cmd->args[0]) != 0)
	{
		perror("chdir");
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			env = shell->env;
			while (env)
			{
				if (strcmp(env->key, "PWD") == 0)
				{
					free(env->value);
					env->value = new_pwd;
					free(old_pwd);
					break ;
				}
				env = env->next;
			}
		}
		else
		{
			perror("getcwd");
		}
		return (0);
	}
	env = shell->env;
	while (env)
	{
		if (strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = old_pwd;
			return (1);
		}
		env = env->next;
	}
	free(old_pwd);
	return (0);
}
