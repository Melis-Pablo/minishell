/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/07 22:42:03 by pmelis           ###   ########.fr       */
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

static char	*get_var_name(char *start, char *end)
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
	strncpy(var_name, start + 1, var_name_len);
	var_name[var_name_len] = '\0';
	return (var_name);
}

static char	*var_to_value(char *word, char *start, char *end, char *var_value)
{
	size_t	new_word_len;
	char	*new_word;

	new_word_len = strlen(word) - (end - start - 1) + strlen(var_value);
	new_word = (char *)malloc(new_word_len + 1);
	if (!new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(new_word, word, start - word);
	new_word[start - word] = '\0';
	strcat(new_word, var_value);
	strcat(new_word, end);
	return (new_word);
}

char	*expand_env_variables(char *word)
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
	while (*end && ((*end == '_') || isalnum(*end)))
		end++;
	var_name = get_var_name(start, end);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	new_word = var_to_value(word, start, end, var_value);
	free(var_name);
	free(word);
	return (new_word);
}

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

int	check_semicolon(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, ";") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == ';')
			return (1);
		if (word[len - 1] == ';')
			return (1);
	}
	return (0);
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
	if (check_semicolon(word))
	{
		free(word);
		perror("Error: Invalid character detected ';'");
		exit(EXIT_FAILURE);
		return (NULL);
	}
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
