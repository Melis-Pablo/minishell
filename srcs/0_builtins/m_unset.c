/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:26:04 by grbuchne          #+#    #+#             */
/*   Updated: 2024/08/01 15:18:46 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
int	split_env(char *str, char **key, char **value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	if (str[len] == '\0')
		return (0);
	*key = (char *)malloc((len + 1) * sizeof(char));
	*value = (char *)malloc((ft_strlen(str) - len) * sizeof(char));
	if (*key == NULL || *value == NULL)
		return (0);
	while (i < len)
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i] = '\0';
	ft_strlcpy(*value, str + len + 1, ft_strlen(str + len + 1) + 1);
	return (1);
}

int	add_to_env_export(t_cmd *cmd, char *str)
{
	t_env	*env;
	t_env	*new_node;
	char	*k;
	char	*v;

	if (!(split_env(str, &k, &v)))
		return (1);

	env = cmd->env;


	while (env != NULL)
	{
		if (ft_strncmp(env->key, k, ft_strlen(str) == 0))
		{
			free(env->value);
			env->value = v;
			free(k);
			return (0);
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		free(k);
		free(v);
		return (1);
	}
	new_node->key = k;
	new_node->value = v;
	new_node->next = NULL;
	if (cmd->env == NULL)
	{
		cmd->env = new_node;
	}
	else
	{
		env->next = new_node;
	}

	return (0);
}*/

int m_unset(t_shell *shell, t_cmd *cmd)
{
    int status = 0;
    if(!cmd->args)
    {
        ft_putstr_fd("unset: not enough arguments", STDERR_FILENO);
        return (1);
    }
    int i = 0;
    while(cmd->args[i])
    {
        if(strchr(cmd->args[i], '='))
        {
            ft_putstr_fd("unset:", STDERR_FILENO);
            ft_putstr_fd(cmd->args[i], STDERR_FILENO);
            ft_putstr_fd("invalid argument", STDERR_FILENO);
            status = 1;
        }
        else
        {
            if (remove_variable(shell, cmd->args[i]) != 1)
                status = 1;
        }
    }
    i++;
}

int remove_variable(t_shell *shell, char *var)
{
    t_env *current;
    t_env *prev;

    current = shell->env;
    prev = NULL;


    while(current)
    {
        if(strncmp(current->key, var, ft_strlen(current->key) + 1) == 0)
        {
            if(prev == NULL)
            {
                shell->env = current->next;
            }
            else
            {
                prev->next == current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return (0);
        }
        prev = current;
        current = current->next;
    }
    return (0);
}

// int main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*s3;
// 	t_cmd	cmd;
// 
// 	cmd.env = NULL;
// 	s1 = "SONNE=Gut";
// 	s2 = "POLIZEI=Nichtso gut";
// 	s3 = "ESSEN=SEHR GUT";
// 
// 	add_to_env_export(&cmd, s1);
// 	add_to_env_export(&cmd, s2);
// 	add_to_env_export(&cmd, s3);
// 	printf("vor unset: \n");
// 	print_env_list(cmd.env);
// 	printf("\n");
// 	m_unset(cmd, "POLIZEI");
// 	printf("nach unset \"POLIZEI\" \n");
// 	print_env_list(cmd.env);
// 	return (0);
// }

////////////////////////////////////////////////////////////////////////////////
//	Kevins /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
int	unset_builtin(t_shell *shell, const t_cmd *cmd)
{
	int	i;

	if (cmd->argc == 0)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
			return (1);
		}
		remove_env(shell, cmd->args[i]);
		i++;
	}
	return (0);
}

*/