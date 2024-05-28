/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/28 15:54:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		signal_status = 0;

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

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
