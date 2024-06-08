/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:21:32 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/08 16:19:58 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////
//                             EXPAND FUNCTIONS                              //
///////////////////////////////////////////////////////////////////////////////

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

static void	reverse_str(char *str, int len)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static void	ft_itoa(int n, char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = (n < 0);
	if (n == 0)
		str[i++] = '0';
	if (sign)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	reverse_str(str, i);
}

static char	*expand_exit_status(char *word, char *start, char *end)
{
	char	*var_value;
	char	*new_word;

	var_value = (char *)malloc(12);
	if (!var_value)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_itoa(g_signal_status, var_value);
	new_word = var_to_value(word, start, end + 1, var_value);
	free(var_value);
	free(word);
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
	if (*end == '?')
		return (expand_exit_status(word, start, end));
	while (*end && ((*end == '_') || isalnum(*end)))
		end++;
	var_name = get_var_name(start, end);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	new_word = var_to_value(word, start, end, var_value);
	free(var_name);
	free(word);
	return (expand_env_variables(new_word));
}

///////////////////////////////////////////////////////////////////////////////
//                             CHECK FUNCTIONS                               //
///////////////////////////////////////////////////////////////////////////////

void	word_error(char *word, int error_code)
{
	char	*error_msg;

	if (error_code == 0)
		return ;
	else if (error_code == 1)
		error_msg = "Error: Invalid character detected ';'\n";
	else if (error_code == 2)
		error_msg = "Error: Invalid character detected '&&'\n";
	else if (error_code == 3)
		error_msg = "Error: Invalid character detected '||'\n";
	else if (error_code == 4)
		error_msg = "Error: Invalid character detected '()'\n";
	else if (error_code == 5)
		error_msg = "Error: Invalid character detected '*'\n";
	else if (error_code == 6)
		error_msg = "Error: Invalid character detected '\\'\n";
	free(word);
	perror(error_msg);
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

int	check_and(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "&&") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '&')
			return (1);
		if (word[len - 1] == '&')
			return (1);
	}
	return (0);
}

int	check_or(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "||") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '|' && word[1] == '|')
			return (1);
		if (word[len - 1] == '|' && word[len - 2] == '|')
			return (1);
	}
	return (0);
}

int	check_wildcard(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "*") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '*')
			return (1);
		if (word[len - 1] == '*')
			return (1);
	}
	return (0);
}

int	check_parentheses(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "()") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '(')
			return (1);
		if (word[len - 1] == ')')
			return (1);
	}
	return (0);
}

int	check_backslash_word(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "\\") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '\\')
			return (1);
		if (word[len - 1] == '\\')
			return (1);
	}
	return (0);
}

int	check_invalid_char(char *word)
{
	int	i;

	i = 0;
	if (check_semicolon(word))
		i = 1;
	if (check_and(word))
		i = 2;
	if (check_or(word))
		i = 3;
	if (check_parentheses(word))
		i = 4;
	if (check_wildcard(word))
		i = 5;
	if (check_backslash_word(word))
		i = 6;
	if (i)
		word_error(word, i);
	return (i);
}

///////////////////////////////////////////////////////////////////////////////
//                             MAIN FUNCTION                                 //
///////////////////////////////////////////////////////////////////////////////
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

int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '\\')
		return (1);
	return (0);
}

int	string_error(char *str)
{
	if (check_unclosed_quote(str))
	{
		if (check_backslash(str))
		{
			perror("Error: Backslash not suported\n");
			return (1);
		}
		perror("Error: Unclosed quote detected\n");
		return (1);
	}
	return (0);
}

static int	count_words(char *str)
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

void	clean_quotes_in_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		array[i] = ft_clean_quotes(array[i]);
		i++;
	}
}
