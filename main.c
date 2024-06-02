/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/02 16:26:23 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		signal_status = 0;

/*
#sigint_handler():	handles the SIGINT signal (ctrl-c)

#Parameters:		int sig

#Return value:		void

#How it works:		
	1. If the signal is SIGINT, set signal_status to 1
	2. Write "minishell> " to stdout
*/
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

/*
#main minishell():	creates a simple shell program

#Parameters:		int argc, char **argv	

#Return value:		int

#How it works:	
	1. Set signal handlers for SIGINT and SIGQUIT
	2. If argc is not 1 or argv[1] is not NULL, print an error message
	3. While 1, read input from the user
	4. If input is NULL, break
	5. Add input to history
	6. Print the input
	7. Free the input
	8. Return 0
*/
int	main(int argc, char **argv)
{
	char	*input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1 || argv[1] != NULL)
	{
		printf("Minishell program does not take arguments. run ./minishell\n");
		return (0);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		////////////////////////////////////////////////////////////////////////
		char **strings = str_blocks(input);
		print_all(strings);
		// t_cmd *head = cmd_builder(strings);
		// print_all_nodes(head);
		clean_blocks(strings);
		////////////////////////////////////////////////////////////////////////
		free(input);
	}
	return (0);
}
