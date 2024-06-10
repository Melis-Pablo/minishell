/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/10 17:41:06 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal_status = 340;

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

int	minishell_loop(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (1);
		add_history(input);
		print_lexed(input);
		//print_strings_and_words(input);
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1 || argv[1] != NULL)
	{
		printf("Minishell program does not take arguments. run ./minishell\n");
		return (0);
	}
	g_signal_status = minishell_loop();
	return (g_signal_status);
}
