/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:05:08 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 17:40:37 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
check_quotes_and_pipes():	Check for pipe outside of quotes.

Arguments:		char *input - the input string.
				int *in_quote - the flag for being in quote.
				char *quote - the quote character.

Return:			int - 1 if the pipe is found, 0 otherwise.

How it works:
	1. If the character is a quote, toggle the in_quote flag.
	2. If the character is a pipe and not in quote, return 1.
	3. Otherwise, return 0.

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
count_pipes():	Count the number of pipes in the input string.

Arguments:		char *input - the input string.

Return:			int count - The number of pipes.

How it works:
	1. Loop through the input string.
	2. If the character is a quote, toggle the in_quote flag.
	3. If the character is a pipe and not in quote, increment the count.
	4. Return the count.
*/
int	count_pipes(char *input)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	// if (unclosed_quotes(input))
	// 	return (0);
	while (*input)
	{
		if (check_quotes_and_pipes(input, &in_quote, &quote))
			count++;
		input++;
	}
	return (count);
}

/*
count_pipe_chars():	Count the number of characters in a pipe.

Arguments:		char *pipe - the pipe string.

Return:			int count - The number of characters.

How it works:
	1. Loop through the pipe string.
	2. If the character is a quote, toggle the in_quote flag.
	3. Increment the count.
	4. Return the count.
*/
int	count_pipe_chars(char *pipe)
{
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	in_quote = 0;
	quote = '\0';
	while (*pipe)
	{
		if (check_quotes_and_pipes(pipe, &in_quote, &quote))
			break ;
		count++;
		pipe++;
	}
	return (count);
}

/*
copy_pipe():	Copy the pipe string.

Arguments:		char *start - the start of the pipe string.

Return:			char *pipe - The copied pipe string.

How it works:
	1. Count the number of characters in the pipe.
	2. Allocate memory for the pipe string.
	3. Loop through the pipe string and copy each character.
	4. Return the pipe string.

*/
char	*copy_pipe(char *start)
{
	int		count;
	char	*pipe;
	int		i;

	i = 0;
	count = count_pipe_chars(start);
	pipe = malloc((count + 1) * sizeof(char));
	if (!pipe)
		return (NULL);
	while (i < count)
	{
		pipe[i] = start[i];
		i++;
	}
	pipe[i] = '\0';
	return (pipe);
}

/*
split_pipeline():	Split the input string into pipes.

Arguments:		char *input - the input string.

Return:			char **pipes - The array of pipes.

How it works:
	1. Count the number of pipes in the input string.
	2. Allocate memory for the array of pipes.
	3. Loop through the input string and copy each pipe.
	4. Return the array of pipes.
*/
char	**split_pipeline(char *input)
{
	int		pipe_count;
	int		i;
	char	**pipes;

	i = 0;
	pipe_count = count_pipes(input);
	pipes = malloc((pipe_count + 2) * sizeof(char *));
	if (!pipes)
		return (NULL);
	while (i <= pipe_count)
	{
		pipes[i] = copy_pipe(input);
		if (!pipes[i])
		{
			free_array(pipes);
			free(pipes);
			return (NULL);
		}
		input += ft_strlen(pipes[i]) + 1;
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}
