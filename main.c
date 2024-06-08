/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/08 17:13:56 by pmelis           ###   ########.fr       */
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

void	print_strings_and_words(char *input)
{
	char	**strings;
	char	**words;
	int		i;

	strings = split_by_pipes(input);
	i = 0;
	while (strings[i] != NULL)
	{
		printf("string: %s\n", strings[i]);
		words = split_into_words(strings[i]);
		if (!words)
		{
			free_array(strings);
			return ;
		}
		clean_quotes_in_array(words);
		print_str_array(words);
		free_array(words);
		i++;
	}
	free_array(strings);
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
		print_strings_and_words(input);
		free(input);
	}
	return (g_signal_status);
}
