/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/29 22:36:46 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_until_pipe(char *input)
{
	int		count;
	int		in_quote;
	char	quote;
	int		i;

	count = 0;
	in_quote = 0;
	quote = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (in_quote && input[i] == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = input[i];
				in_quote = 1;
			}
		}
		else if (input[i] == '|' && !in_quote)
			break ;
		count++;
		i++;
	}
	return (count);
}

int	count_pipes(char *input)
{
	int		count;
	int		in_quote;
	char	quote;
	int		i;

	count = 0;
	in_quote = 0;
	quote = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (in_quote && input[i] == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = input[i];
				in_quote = 1;
			}
		}
		else if (input[i] == '|' && !in_quote)
			count++;
		i++;
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

char	**str_blocks(char *input)
{
	int		pipe_count;
	int		i;
	char	**blocks;

	i = 0;
	pipe_count = count_pipes(input);
	blocks = malloc((pipe_count + 1) * sizeof(char *));
	if (!blocks)
		return (NULL);
	while (i <= pipe_count)
	{
		blocks[i] = copy_until_pipe(input);
		input += strlen(blocks[i]) + 1;
		i++;
	}
	blocks[i] = NULL;
	return (blocks);
}
