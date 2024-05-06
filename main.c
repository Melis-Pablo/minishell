/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/06 14:09:47 by pmelis           ###   ########.fr       */
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
