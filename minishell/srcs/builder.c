/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:06:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 15:14:51 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*builder(char *input, t_shell *shell)
{
	char	**token_arr;
	t_token	*token_lst;
	t_cmd	*cmd_lst;

	token_arr = split_tokens(input);
	if (!token_arr)
		return (NULL);
	token_lst = lexer(token_arr);
	free_array(token_arr);
	if (!token_lst)
		return (NULL);
	if (syntax_error(token_lst))
	{
		free_tokens(token_lst);
		return (NULL);
	}
	token_lst = env_expand(token_lst, shell);
	if (!token_lst)
		return (NULL);
	cmd_lst = parser(token_lst);
	free_tokens(token_lst);
	if (!cmd_lst)
		return (NULL);
	return (cmd_lst);
}
