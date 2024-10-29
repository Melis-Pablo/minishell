/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:26:33 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 20:02:06 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_delimiter(char *input, int *in_quote, char *quote)
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
	else if (!*in_quote && (*input == '|'
			|| *input == '<' || *input == '>' || ft_is_space(*input)))
		return (1);
	return (0);
}

int	handle_delimiter(char **input, int *count, int *in_token)
{
	char	quote;
	int		in_quote;

	quote = '\0';
	in_quote = 0;
	if (check_delimiter(*input, &in_quote, &quote))
	{
		if (*in_token)
		{
			(*count)++;
			*in_token = 0;
		}
		if (**input == '|' || **input == '<' || **input == '>')
		{
			(*count)++;
			while (**input == '|' || **input == '<' || **input == '>')
				(*input)++;
			return (1);
		}
	}
	return (0);
}

int	count_tokens(char *input)
{
	int		count;
	int		in_token;

	count = 0;
	in_token = 0;
	while (*input)
	{
		if (handle_delimiter(&input, &count, &in_token))
			continue ;
		else
			in_token = 1;
		input++;
	}
	if (in_token)
		count++;
	return (count);
}

char	**split_tokens(char *input)
{
	int		token_count;
	char	**tokens;
	char	*token;
	int		i;

	token = NULL;
	i = 0;
	token_count = count_tokens(input);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (*input)
	{
		if (ft_is_space(*input))
		{
			input++;
			continue ;
		}
		token = get_token(&input);
		if (token)
			tokens[i++] = token;
	}
	tokens[i] = NULL;
	return (tokens);
}
