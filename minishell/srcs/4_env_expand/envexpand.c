/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envexpand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:51:15 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 15:30:40 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *start, char *end)
{
	size_t	var_name_len;
	char	*var_name;

	var_name_len = end - start - 1;
	var_name = (char *)malloc(var_name_len + 1);
	if (!var_name)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(var_name, start + 1, var_name_len);
	var_name[var_name_len] = '\0';
	return (var_name);
}

char	*var_to_value(char *word, char *start, char *end, char *var_value)
{
	size_t	new_word_len;
	char	*new_word;

	new_word_len = ft_strlen(word) - (end - start - 1) + ft_strlen(var_value);
	new_word = (char *)malloc(new_word_len + 1);
	if (!new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(new_word, word, start - word);
	new_word[start - word] = '\0';
	ft_strcat(new_word, var_value);
	ft_strcat(new_word, end);
	return (new_word);
}

char	*expand_exit_status(char *word, char *start, char *end, t_shell *shell)
{
	char	*var_value;
	char	*new_word;

	var_value = (char *)malloc(12);
	if (!var_value)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_itoa(shell->last_status, var_value);
	new_word = var_to_value(word, start, end + 1, var_value);
	free(var_value);
	free(word);
	return (new_word);
}

char	*get_var_value(char *var_name, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(var_name, current->key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_env_variables(char *word, t_shell *shell)
{
	char	*start;
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*new_word;

	start = strchr(word, '$');
	if (!start)
		return (word);
	end = start + 1;
	if (*end == '?')
		return (expand_exit_status(word, start, end, shell));
	while (*end && ((*end == '_') || ft_isalnum(*end)))
		end++;
	var_name = get_var_name(start, end);
	var_value = get_var_value(var_name, shell->env);
	if (!var_value)
		var_value = "";
	new_word = var_to_value(word, start, end, var_value);
	free(var_name);
	free(word);
	return (expand_env_variables(new_word, shell));
}
