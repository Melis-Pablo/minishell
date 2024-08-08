/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:32:33 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/08 19:02:35 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_cd_args(t_cmd *cmd, char **old_pwd)
{
	if (cmd->args && cmd->args[0] && cmd->args[1])
	{
		ft_putendl_fd("cd: too many arguments\n", STDERR_FILENO);
		free(*old_pwd);
		return (1);
	}
	return (0);
}

static int	change_directory(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0] || strcmp(cmd->args[0], "~") == 0
		|| strcmp(cmd->args[0], "HOME") == 0)
		return (get_home(&shell->env));
	else if (strcmp(cmd->args[0], "..") == 0)
		return (get_up(shell));
	else if (chdir(cmd->args[0]) != 0)
		return (ft_perror("chdir", 1));
	return (0);
}

static int	update_pwd1(t_shell *shell)
{
	char	*new_pwd;
	t_env	*env;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_perror("getcwd", 1));
	env = shell->env;
	while (env)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = new_pwd;
			return (0);
		}
		env = env->next;
	}
	free(new_pwd);
	return (1);
}

static int	update_oldpwd(t_shell *shell, char *old_pwd)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = old_pwd;
			return (0);
		}
		env = env->next;
	}
	free(old_pwd);
	return (1);
}

int	m_cd(t_shell *shell, t_cmd *cmd)
{
	char	*old_pwd;
	int		result;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_perror("getcwd", 1));
	if (handle_cd_args(cmd, &old_pwd) != 0)
		return (1);
	result = change_directory(shell, cmd);
	if (result != 0)
	{
		free(old_pwd);
		return (result);
	}
	result = update_pwd1(shell);
	if (result != 0)
	{
		free(old_pwd);
		return (result);
	}
	return (update_oldpwd(shell, old_pwd));
}

/*
	//////////////////////OLD VERSION///////////////////////
int	m_cd(t_shell *shell, t_cmd *cmd)
{
	char	*old_pwd;
	int		result;
	char	*new_pwd;
	t_env	*env;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_perror("getcwd"));
	if (cmd->args && cmd->args[0] && cmd->args[1])
	{
		ft_putendl_fd("cd: too many arguments\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	result = 0;
	if (!cmd->args || !cmd->args[0] || strcmp(cmd->args[0], "~") == 0
		||strcmp(cmd->args[0], "HOME") == 0)
		result = get_home(&shell->env);
	else if (strcmp(cmd->args[0], "..") == 0)
		result = get_up(shell);
	else
	{
		if (chdir(cmd->args[0]) != 0)
		{
			perror("chdir");
			free(old_pwd);
			return (1);
		}
		new_pwd = getcwd(NULL, 0);
		if (!new_pwd)
		{
			perror("getcwd");
			free(old_pwd);
			return (1);
		}
		env = shell->env;
		while (env)
		{
			if (strcmp(env->key, "PWD") == 0)
			{
				free(env->value);
				env->value = new_pwd;
				break ;
			}
			env = env->next;
		}
	}
	env = shell->env;
	while (env)
	{
		if (strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = old_pwd;
			return (result);
		}
		env = env->next;
	}
	free(old_pwd);
	return (result);
}


///////////////////////////////invalid funktions//////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////


int	get_home(t_env **env)
{
	t_env	*current;
	char	*home_path;
	char	*new_pwd;

	current = *env;
	home_path = NULL;
	while (current)
	{
		if (strcmp(current->key, "HOME") == 0)
		{
			home_path = current->value;
			break ;
		}
		current = current->next;
	}
	if (!home_path)
	{
		ft_putendl_fd("HOME not set in environment", STDERR_FILENO);
		return (1);
	}
	if (chdir(home_path) != 0)
		return (ft_perror("chdir"));
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_perror("get_cwd"));
	current = *env;
	while (current)
	{
		if (strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = new_pwd;
			return (0);
		}
		current = current->next;
	}
	free(new_pwd);
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
	if (cmd->args && cmd->args[0] && cmd->args[1])
	{
		ft_putendl_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		if (get_home(&shell->env) != 0)
			ft_putendl_fd("Failed to change to HOME directory\n",
				STDERR_FILENO);
	}
	else if (strcmp(cmd->args[0], "~") == 0)
	{
		if (get_home(&shell->env) != 0)
			ft_putendl_fd("Failed to change to HOME directory\n",
				STDERR_FILENO);
	}
	else if (strcmp(cmd->args[0], "..") == 0)
	{
		if (get_up(shell) != 0)
			ft_putendl_fd("Failed to change to parent directory\n",
				STDERR_FILENO);
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
					env->value = ft_strdup(new_pwd);
					free(new_pwd);
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
			index = get_parent_directory_index(env->value);
			if (index > 0)
			{
				new_pwd = strndup(env->value, index);
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
*/