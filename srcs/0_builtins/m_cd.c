/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/01 15:16:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

int get_home(t_env **env)
{
	t_env *i = *env;
	char *path;

	while (i != NULL)
	{
		if (strcmp(i->key, "HOME") == 0)
		{
			if (chdir(i->value) == 0)
			{
				path = getcwd(NULL, 0);
				if (path)
				{
					t_env *k = *env;
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

int get_parent_directory_index(const char *str)
{
	int i = strlen(str) - 1;
	while (i > 0 && str[i] != '/')
		i--;
	return i;
}

int get_up(t_cmd *cmd)
{
	t_env *env = cmd->env;
	while (env != NULL)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			int index = get_parent_directory_index(env->value);
			if (index > 0)
			{
				char *new_pwd = strndup(env->value, index);
				if (new_pwd)
				{
					free(env->value);
					env->value = new_pwd;
					return (0);
				}
			}
			return (1);  
		}
		env = env->next;
	}
	return (1);  
}

void change_directory(t_cmd *cmd)
{
	char *old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		return;
	}

	if (!cmd->args || !cmd->args[0])
	{
		if (get_home(&cmd->env) != 0)
			fprintf(stderr, "Failed to change to HOME directory\n");
	}
	else if (strcmp(cmd->args[0], "~") == 0)
	{
		if (get_home(&cmd->env) != 0)
			fprintf(stderr, "Failed to change to HOME directory\n");
	}
	else if (strcmp(cmd->args[0], "..") == 0)
	{
		if (get_up(cmd) != 0)
			fprintf(stderr, "Failed to change to parent directory\n");
	}
	else if (chdir(cmd->args[0]) != 0)
	{
		perror("chdir");
	}
	else
	{
		char *new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			t_env *env = cmd->env;
			while (env)
			{
				if (strcmp(env->key, "PWD") == 0)
				{
					free(env->value);
					env->value = new_pwd;
					break;
				}
				env = env->next;
			}
		}
		else
		{
			perror("getcwd");
		}
	}

	t_env *env = cmd->env;
	while (env)
	{
		if (strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = old_pwd;
			return;
		}
		env = env->next;
	}
	free(old_pwd);  
}

////////////////////////////////////////////////////////////////////////////////
//	Kevins /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
int	set_env_vars(t_shell *shell, const char *path)
{
	char	*old_pwd;
	char	*pwd;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	old_pwd = get_env(shell->secret_env, "PWD");
	pwd = getcwd(0, 0);
	set_env(shell, "OLDPWD", old_pwd);
	set_env(shell, "PWD", pwd);
	set_secret_env(shell, "OLDPWD", old_pwd);
	set_secret_env(shell, "PWD", pwd);
	free(old_pwd);
	free(pwd);
	return (0);
}

int	cd_builtin(t_shell *shell, const t_cmd *cmd)
{
	char	*path;

	if (cmd->argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd->argc)
		path = get_env(shell->secret_env, "HOME");
	else
		path = cmd->args[0];
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (set_env_vars(shell, path));
}

*/