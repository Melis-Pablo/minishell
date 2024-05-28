/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/28 16:06:35 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
#print_str_array():	prints a string array

#Parameters:		char **str_array

#Return value:		void

#How it works:		
	1. If the array is NULL, print "The array is empty."
	2. Loop through the array and print each string with its index
*/
void	print_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array == NULL)
	{
		printf("The array is empty.\n");
		return ;
	}
	while (str_array[i])
	{
		printf("String %d: %s\n", i, str_array[i]);
		i++;
	}
	return ;
}

/*
#main minishell():	creates a simple shell program

#Parameters:		int argc, char **argv	

#Return value:		int

#How it works:		
	1. Set signal handlers for SIGINT and SIGQUIT
	2. If there are arguments, print an error message and return 0
	3. Loop until the user presses ctrl-d
	4. Read input from the user
	5. If there is no input, break the loop
	6. Add the input to the history
	7. Print the input
	8. Free the input
	9. Return 0
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
		char **strings = string_blocks(input);
		print_str_array(strings);
		////////////////////////////////////////////////////////////////////////
		free(input);
	}
	return (0);
}
