/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/10 20:10:11 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
is_space():	Checks if a character is a space

Parameters:	char c - the character to check

Return:		int - 1 if the character is a space, 0 otherwise

How it works:
	1. Check if the character is a space
	2. Return 1 if it is, 0 otherwise
*/
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

/*
reverse_str():	Reverses a string

Parameters:		char *str - the string to reverse
				int len - the length of the string

Return:			void

How it works:
	1. Loop through the string
	2. Swap the characters at the beginning and end of the string
*/
void	reverse_str(char *str, int len)
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

/*
ft_itoa():	Converts an integer to a string

Parameters:	int n - the integer to convert
			char *str - the string to store the result

Return:		void

How it works:
	1. Check if the number is negative
	2. Loop through the number
	3. Add the digits to the string
	4. Add a '-' if the number is negative
	5. Add a null terminator at the end of the string
	6. Reverse the string
*/
void	ft_itoa(int n, char *str)
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

/*
ft_clean_quotes():	Removes quotes from a word

Parameters:			char *word - the word to clean

Return:				char * - the cleaned word

How it works:
	1. Check if the word is surrounded by quotes
	2. Remove the quotes
	3. Expand environment variables
	4. Free the original word
	5. Return the cleaned word
*/
char	*ft_clean_quotes(char *word)
{
	char	*new_word;

	if (word[0] == '"' && word[ft_strlen(word) - 1] == '"')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		new_word = expand_env_variables(new_word);
		free(word);
		return (new_word);
	}
	else if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
	{
		new_word = ft_strndup(word + 1, ft_strlen(word) - 2);
		free(word);
		return (new_word);
	}
	else
		return (word);
}

/*
clean_quotes_in_array():	Cleans quotes in an array of strings

Parameters:					char **array - the array of strings to clean

Return:						void

How it works:
	1. Loop through the array
	2. Clean the quotes in each string
*/
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

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
