/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/16 16:45:11 by pmelis           ###   ########.fr       */
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
void	sigint_handler(int sig)
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
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		printf("------------------------------------\n");
		printf("Node Address: %p\n", (void *)current);
		printf("Prev Node Address: %p\n", (void *)current->prev);
		printf("Next Node Address: %p\n", (void *)current->next);
		printf("Token Number: %d\n", current->index);
		printf("Token String: %s\n", current->str);
		printf("Token Type: %d\n", current->token);
		printf("------------------------------------\n");
		current = current->next;
	}
}

void print_str_array(char **str_array)
{
    if (str_array == NULL)
    {
        printf("The array is empty.\n");
        return;
    }

    for (int i = 0; str_array[i] != NULL; i++)
    {
        printf("String %d: %s\n", i, str_array[i]);
    }
}

/*
#main():		Minishell program

#Parameters:	int argc
				char **argv

#Return value:	Exit Status

#How it works:	1. Declares input variable
				2. SIGINT (CTRL-C) prints new prompt
				3. SIGQUIT (CTRL-\) nothing
					If (./minishell) has any arguments
					throw error
				4. Infinite loop to run minishell
				5. Readline into input
				6. CTR-D check, ends program
				7. Adds history
				8. test lexer
				9. prints lexer
				10. free input
				11. free lexer
				12. return 0

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
		// t_lexer *head = lexer(input);
		// print_lexer_nodes(head);
		char **strings = string_blocks(input);
		print_str_array(strings);
		free(input);
		//clear_lexer(head);
	}
	return (0);
}
