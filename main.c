/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/04/29 19:07:31 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		signal_status = 0;

// Signal handler for SIGINT and SIGQUIT
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

t_lexer	*lexer(char *input)
{

}


int	main(void)
{
	char	*input;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		free(input);
	}
	return (0);
}
