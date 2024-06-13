/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:18:47 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:35:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_words(char *str)
{
	int	count;
	int	in_quotes;

	if (string_error(str))
		return (0);
	count = 0;
	in_quotes = 0;
	while (*str && is_space(*str))
		str++;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && *str == ' '
			&& *(str + 1) != ' '
			&& *(str + 1) != '\0')
			count++;
		str++;
	}
	return (count + 1);
}

char	*get_word(char **str)
{
	char	*word;
	int		i;

	i = 0;
	while ((*str)[i] && !is_space((*str)[i]))
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '\'')
				i++;
		}
		i++;
	}
	word = ft_strndup(*str, i);
	if (check_invalid_char(word))
		return (NULL);
	*str += i;
	return (word);
}

char	**split_into_words(char *str)
{
	int		word_count;
	char	**words;
	int		i;

	i = 0;
	while (*str && is_space(*str))
		str++;
	word_count = count_words(str);
	words = malloc(sizeof(char *) * (word_count + 1));
	while (i < word_count)
	{
		while (*str && is_space(*str))
			str++;
		words[i] = get_word(&str);
		if (!words[i])
		{
			free_array(words);
			return (NULL);
		}
		while (*str && is_space(*str))
			str++;
		i++;
	}
	words[word_count] = NULL;
	return (words);
}
