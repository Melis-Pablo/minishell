/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/09 17:09:34 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		signal_status = 0;

/*
#signal_handler():	Signal handler for SIGINT and SIGQUIT

#Parameters:		int sig

#Return value:		void

#How it works:		1. if SIGINT
						2. set signal to 1
						3. write new prompt
					4. else (SIGQUIT)
						5. Do nothing
*/
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

/*
#print_lexer_nodes():	prints nodes and whats inside

#Parameters:			t_lexer *head

#Return value:			void

#How it works:			goes until end of list and prints elements
*/
void	print_lexer_nodes(t_lexer *head)
{
	t_lexer *current = head;

	while (current != NULL)
	{
		printf("------------------------------------\n");
		printf("Token Number: %d\n", current->index);
		printf("Token String: %s\n", current->str);
		printf("Token Type: %d\n", current->token);
		printf("------------------------------------\n");
		current = current->next;
	}
}

/*
#main():		Minishell program

#Parameters:	

#Return value:	Exit Status

#How it works:	1. Declares input variable
				2. SIGINT (CTRL-C) prints new prompt
				3. SIGQUIT (CTRL-\) nothing
				4. Infinite loop to run minishell
				5. Readline into input
				6. CTR-D check, ends program
				7. Adds history
				8. test lexer
				9. prints lexer
				10. free input
				11. return 0

*/
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
		t_lexer *head = lexer(input);
		print_lexer_nodes(head);
		free(input);
	}
	return (0);
}
