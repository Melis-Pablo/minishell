/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:05:08 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:33:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		input += ft_strlen(strings[i]) + 1;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
