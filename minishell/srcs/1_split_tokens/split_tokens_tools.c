/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:33:06 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 19:34:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_token_str(char *start, int len)
{
	char	*token;

	token = (char *)malloc(len + 1);
	if (token)
	{
		ft_strncpy(token, start, len);
		token[len] = '\0';
	}
	return (token);
}

int	is_special_token(char **input, char **start, int *len)
{
	if (**input == '|' || **input == '<' || **input == '>')
	{
		*start = *input;
		while (**input == '|' || **input == '<' || **input == '>')
		{
			(*input)++;
		}
		*len = *input - *start;
		return (1);
	}
	return (0);
}

char	*get_token(char **input)
{
	int		in_quote;
	char	quote;
	char	*start;
	int		len;

	in_quote = 0;
	quote = '\0';
	start = *input;
	len = 0;
	while (**input)
	{
		if (check_delimiter(*input, &in_quote, &quote))
		{
			if (len > 0 || is_special_token(input, &start, &len))
				break ;
		}
		else
		{
			if (len == 0)
				start = *input;
			len++;
		}
		(*input)++;
	}
	return (create_token_str(start, len));
}
