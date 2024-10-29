/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_envexpand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:29:51 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 16:05:48 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_clean_quotes(char *word, t_shell *shell)
{
	char	*new_word;

	new_word = NULL;
	if (word[0] == '"' && word[ft_strlen(word) - 1] == '"')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		new_word = expand_env_variables(new_word, shell);
		free(word);
		return (new_word);
	}
	else if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		free(word);
		return (new_word);
	}
	else if (word[0] == '$')
	{
		if (ft_strlen(word) == 1)
			return (word);
		new_word = expand_env_variables(word, shell);
		return (new_word);
	}
	else
		return (word);
}

t_token	*env_expand(t_token *head, t_shell *shell)
{
	t_token	*current;

	current = head;
	while (current)
	{
		current->word = ft_clean_quotes(current->word, shell);
		current = current->next;
	}
	return (head);
}
