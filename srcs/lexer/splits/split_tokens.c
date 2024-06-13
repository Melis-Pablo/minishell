/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:18:47 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 17:40:30 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
//Split tokens by < and >
/*
count_tokens():	Count the number of tokens in the input string.

Arguments:		char *pipe - the input string.

Return:			int count - The number of tokens.

How it works:
	1. Loop through the input string.
	2. If the character is a quote, toggle the in_quote flag.
	3. If the character is a space and not in quote, increment the count.
	4. Return the count.
*/
int	count_tokens(char *pipe)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	// if (unclosed_quotes(pipe))
	// 	return (0);
	while (*pipe && ft_is_space(*pipe))
		pipe++;
	while (*pipe)
	{
		if (*pipe == '"' || *pipe == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && *pipe == ' '
			&& *(pipe + 1) != ' '
			&& *(pipe + 1) != '\0')
			count++;
		pipe++;
	}
	return (count + 1);
}

/*
get_token():	Get the next token from the input string.

Arguments:		char **pipe - the input string.

Return:			char *token - The token.

How it works:
	1. Loop through the input string.
	2. If the character is a quote, skip until the closing quote.
	3. Return the token.
*/
char	*get_token(char **pipe)
{
	char	*token;
	int		i;

	i = 0;
	while ((*pipe)[i] && !ft_is_space((*pipe)[i]))
	{
		if ((*pipe)[i] == '"' || (*pipe)[i] == '\'')
		{
			i++;
			while ((*pipe)[i] && (*pipe)[i] != '"' && (*pipe)[i] != '\'')
				i++;
		}
		i++;
	}
	token = ft_strndup(*pipe, i);
	*pipe += i;
	return (token);
}

/*
split_tokens():	Split the input string into tokens.

Arguments:		char *pipe - the input string.

Return:			char **tokens - The array of tokens.

How it works:
	1. Count the number of tokens in the input string.
	2. Allocate memory for the array of tokens.
	3. Loop through the input string and get each token.
	4. Return the array of tokens.
*/
char	**split_tokens(char *pipe)
{
	int		token_count;
	char	**tokens;
	int		i;

	i = 0;
	while (*pipe && ft_is_space(*pipe))
		pipe++;
	token_count = count_tokens(pipe);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	while (i < token_count)
	{
		while (*pipe && ft_is_space(*pipe))
			pipe++;
		tokens[i] = get_token(&pipe);
		if (!tokens[i])
		{
			free_array(tokens);
			return (NULL);
		}
		while (*pipe && ft_is_space(*pipe))
			pipe++;
		i++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
