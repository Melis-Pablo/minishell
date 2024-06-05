/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/05 17:56:54 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
check_quotes_and_pipes():	Check if the character is a quote or a pipe
							and toggle the in_quote flag

Parameters:					char *input - the character to check

Return:						int - 1 if the character is a pipe, 0 otherwise

How it works:
	1. If the character is a quote
		2. If in quotes and the character is the same as the quote
			3. Toggle the in_quote flag
		4. If not in quotes
			5. Set the quote to the character
			6. Toggle the in_quote flag
	7. If the character is a pipe and not in quotes
		8. Return 1
	9. Return 0
*/
int	check_quotes_and_pipes(char *input, int *in_quote, char *quote)
{
	if (*input == '\'' || *input == '\"')
	{
		if (*in_quote && *input == *quote)
			*in_quote = 0;
		else if (!*in_quote)
		{
			*quote = *input;
			*in_quote = 1;
		}
	}
	else if (*input == '|' && !*in_quote)
		return (1);
	return (0);
}

/*
count_pipes():	Count the number of pipes in the string

Parameters:		char *input - the string to count pipes in

Return:			int - the number of pipes

How it works:
	1. Initialize the count to 0
	2. Initialize the in_quote flag to 0
	3. Initialize the quote to '\0'
	4. Loop through the string
		5. If the character is a quote
			6. If in quotes and the character is the same as the quote
				7. Toggle the in_quote flag
			8. If not in quotes
				9. Set the quote to the character
				10. Toggle the in_quote flag
		11. If the character is a pipe and not in quotes
			12. Increment the count
		13. Move to the next character
	14. Return the count
*/
int	count_pipes(char *input)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	while (*input)
	{
		if (check_quotes_and_pipes(input, &in_quote, &quote))
			count++;
		input++;
	}
	return (count);
}

/*
count_until_pipe():	Count the number of characters until the next pipe

Parameters:			char *input - the string to count characters in

Return:				int - the number of characters until the next pipe

How it works:
	1. Initialize the count to 0
	2. Initialize the in_quote flag to 0
	3. Initialize the quote to '\0'
	4. Loop through the string
		5. If the character is a quote
			6. If in quotes and the character is the same as the quote
				7. Toggle the in_quote flag
			8. If not in quotes
				9. Set the quote to the character
				10. Toggle the in_quote flag
		11. If the character is a pipe and not in quotes
			12. Break the loop
		13. Increment the count
		14. Move to the next character
	15. Return the count
*/
int	count_until_pipe(char *input)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	while (*input)
	{
		if (check_quotes_and_pipes(input, &in_quote, &quote))
			break ;
		count++;
		input++;
	}
	return (count);
}

/*
copy_until_pipe():	Copy characters from the string until the next pipe

Parameters:			char *start - the string to copy characters from

Return:				char * - the copied string

How it works:
	1. Count the number of characters until the next pipe
	2. Allocate memory for the new string
	3. Loop through the string up to the count
		4. Copy each character to the new string
	5. Add the null terminator
	6. Return the new string
*/
char	*copy_until_pipe(char *start)
{
	int		count;
	char	*str;
	int		i;

	i = 0;
	count = count_until_pipe(start);
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < count)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
split_by_pipes():	Split the string by pipes

Parameters:			char *input - the string to split

Return:				char ** - the array of strings

How it works:
	1. Count the number of pipes
	2. Allocate memory for the array of strings
	3. Loop through the pipes
		4. Copy the string until the next pipe
		5. Move the input pointer to the next string
	6. Return the array of strings
*/
char	**split_by_pipes(char *input)
{
	int		pipe_count;
	int		i;
	char	**strings;

	i = 0;
	pipe_count = count_pipes(input);
	strings = malloc((pipe_count + 2) * sizeof(char *));
	if (!strings)
		return (NULL);
	while (i <= pipe_count)
	{
		strings[i] = copy_until_pipe(input);
		input += strlen(strings[i]) + 1;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
