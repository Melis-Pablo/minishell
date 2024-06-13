/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:37:05 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 17:25:15 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	error_check(t_cmd *head_cmd)
{
	t_cmd	*tmp_cmd;
	t_lexer	*tmp_lexer;

	tmp_cmd = head_cmd;
	while (tmp_cmd)
	{
		tmp_lexer = tmp_cmd->lexer;
		while (tmp_lexer)
		{
			if (unclosed_quotes(tmp_lexer->word))
			{
				printf("Error: Unclosed quotes detected in: %s\n", tmp_lexer->word);
				return (1);
			}
			if (check_invalid_char(tmp_lexer->word))
			{
				printf("parse error near: %s\n", tmp_lexer->word);
				return (1);
			}
			if (tmp_lexer->type != 0 && !tmp_lexer->word[0])
			{
				printf("parse error near: %s\n", tmp_lexer->prev->word);
				return (1);
			}
			tmp_lexer = tmp_lexer->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

int	expand_all(t_cmd *head_cmd)
{
	t_cmd	*tmp_cmd;
	t_lexer	*tmp_lexer;

	tmp_cmd = head_cmd;
	while (tmp_cmd)
	{
		tmp_lexer = tmp_cmd->lexer;
		while (tmp_lexer)
		{
			ft_clean_quotes(tmp_lexer->word);
			tmp_lexer = tmp_lexer->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
