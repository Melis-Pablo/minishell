/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 17:45:30 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		signal_status = 0;

/*
sigint_handler():	the signal handler for SIGINT

Parameters:			int sig - the signal number

Return:				void

How it works:
	1. If the signal is SIGINT, set signal_status to 1
	2. Write "minishell> " to the standard output
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
main():		the main function of the minishell program

Parameters:	int argc - the number of arguments
			char **argv - the array of arguments

Return:		int - the exit status of the program

How it works:
	1. Set the signal handler for SIGINT to sigint_handler
	2. Ignore the signal for SIGQUIT
	3. Check if the program was run without arguments
	4. Loop forever
		5. Read a line from the user
		6. If the input is NULL, break the loop
		7. Add the input to the history
		8. Build the linked list of commands from the input
		9. Print the linked list of commands
		10. Free the linked list of commands
	11. Return signal_status
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

		t_cmd *head = cmd_builder(input);
		print_cmds_list(head);
		free_cmds(head);


		free(input);
	}
	return (signal_status);
}
