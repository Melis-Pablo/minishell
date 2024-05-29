/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 23:12:58 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/29 13:37:23 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		signal_status = 0;

//	Signal handler for SIGINT
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal_status = 1;
		write(1, "\nminishell> ", 12);
	}
}

//	prints the string arrays created by string_blocks
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

//	prints the words created by split_string
void print_words(char **words) {
    if (words == NULL) {
        printf("The array is empty.\n");
        return;
    }

    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
    }
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
		///////////////////////////////////////
		char **strings = string_blocks(input);	//	creates an array of strings from the input
		print_str_array(strings);
		char **words = split_string(input);		//	creates an array of words from the input
		print_words(words);
		///////////////////////////////////////
		free(input);
	}
	return (0);
}
