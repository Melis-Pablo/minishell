/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/07 17:34:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	check_unclosed_quote(char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (!double_quotes)
				single_quotes = !single_quotes;
		}
		else if (*str == '"')
		{
			if (!single_quotes)
				double_quotes = !double_quotes;
		}
		str++;
	}
	if (single_quotes || double_quotes)
		return (1);
	else
		return (0);
}

static int	count_words(char *str)
{
	int	count;
	int	in_quotes;

	if (check_unclosed_quote(str))
	{
		printf("Error: Unclosed quote detected\n");
		exit(1);
	}
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

///////////////////////////////////////////////////////////////////////////////

static char	*get_env_value(const char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return (strdup(""));
	return (strdup(value));
}

static int	calculate_new_length(char *word)
{
	int		len;
	int		i;
	int		start;
	char	*env_value;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && (isalpha(word[i + 1]) || word[i + 1] == '_'))
		{
			i++;
			start = i;
			while (word[i] && (isalnum(word[i]) || word[i] == '_'))
				i++;
			env_value = get_env_value(strndup(word + start, i - start));
			len += strlen(env_value);
			free(env_value);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*expand_env_variables(char *word)
{
	int		i;
	int		j;
	int		start;
	char	*expanded_str;
	char	*env_value;

	if (!word)
		return (NULL);
	expanded_str = (char *)malloc(calculate_new_length(word) + 1);
	if (!expanded_str)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && (isalpha(word[i + 1]) || word[i + 1] == '_'))
		{
			i++;
			start = i;
			while (word[i] && (isalnum(word[i]) || word[i] == '_'))
				i++;
			env_value = get_env_value(strndup(word + start, i - start));
			strcpy(expanded_str + j, env_value);
			j += strlen(env_value);
			free(env_value);
		}
		else
			expanded_str[j++] = word[i++];
	}
	expanded_str[j] = '\0';
	free(word);
	return (expanded_str);
}


///////////////////////////////////////////////////////////////////////////////

char	*ft_clean_quotes(char *word)
{
	char	*new_word;

	if (word[0] == '"' && word[strlen(word) - 1] == '"')
	{
		new_word = ft_strndup(word + 1, strlen(word) - 2);
		new_word = expand_env_variables(new_word);
		free(word);
		return (new_word);
	}
	else if (word[0] == '\'' && word[strlen(word) - 1] == '\'')
	{
		new_word = ft_strndup(word + 1, strlen(word) - 2);
		free(word);
		return (new_word);
	}
	else
		return (word);
}

static char	*get_word(char **str)
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
	word = ft_clean_quotes(word);
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
		while (*str && is_space(*str))
			str++;
		i++;
	}
	words[word_count] = NULL;
	return (words);
}
