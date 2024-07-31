/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:06:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/24 20:00:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	build_exec(char *input)
{
	char	**token_arr;
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	int		exit_status;

	exit_status = 0;
/////////////////////////////////////////////////////////////////
	//Split Tokens [String Array]////////////////////////////////
	token_arr = split_tokens(input);
	if (!token_arr)
		return (1);
	// print_str_array(token_arr);
/////////////////////////////////////////////////////////////////
	//Lexer [Token Linked List]
	token_lst = lexer(token_arr);
	free_array(token_arr);
	if (!token_lst)
		return (1);
	// printf("Lexer Output:\n");
	// print_tokens(token_lst);
/////////////////////////////////////////////////////////////////
	//Syntax error check
	if (syntax_error(token_lst))
	{
		free_tokens(token_lst);
		return (2);
	}
	// printf("Syntax Error Check Passed\n");
	// print_tokens(token_lst);
/////////////////////////////////////////////////////////////////
	//Env Expansion [IMPLEMENT BUILTIN ENV]
	token_lst = env_expand(token_lst);
	if (!token_lst)
		return (1);
	// printf("Env Expansion Output:\n");
	// print_tokens(token_lst);
/////////////////////////////////////////////////////////////////
	//Parser [Command Linked List]
	cmd_lst = parser(token_lst);
	printf("Parser Output:\n");
	print_cmds(cmd_lst);
	free_tokens(token_lst);
	if (!cmd_lst)
		return (1);
	//Execute Commands
	exit_status = exec_cmds(cmd_lst);
	free_cmds(cmd_lst);
	return (exit_status);
}
