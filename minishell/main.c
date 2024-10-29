/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:14:28 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 13:56:01 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	next_run(t_shell *shell)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		shell->exit = 1;
		return ;
	}
	if (*input)
		add_history(input);
	execute(shell, input, &shell->last_status);
	free(input);
}

int	miniloop(char **env)
{
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.first_run = 1;
	shell.envc = 0;
	parse_env(env, &shell);
	signal_handler();
	while (!shell.exit)
		next_run(&shell);
	free_env(shell.env);
	return (shell.last_status);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	return (miniloop(env));
}
