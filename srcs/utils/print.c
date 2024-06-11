/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:29:09 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/11 17:09:42 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array():	Prints an array of strings

Parameters:			char **arr - the array of strings to print

Return:				void

How it works:
	1. Loop through the array of strings
	2. Print each string with an index
*/
void	print_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("Word[%i] %s\n", i, arr[i]);
		i++;
	}
	printf("\n");
}

/*
print_strings_and_words():	Prints the strings and words from the input

Parameters:					char *input - the input string

Return:						void

How it works:
	1. Split the input by pipes
	2. Loop through the strings
		3. Print the string
		4. Split the string into words
		5. Print the words
	6. Free the strings
*/
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
		print_str_array(words);
		free_array(words);
		i++;
	}
	free_array(strings);
}

/*
print_lexer_list():	Prints the lexer list

Parameters:			t_lexer *head - the head of the lexer list

Return:				void

How it works:
	1. Loop through the lexer list
		2. Print the word and the type
	3. Free the lexer list
*/
void	print_lexer_list(t_lexer *head)
{
	t_lexer	*tmp;
	char	*type_str;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == REDIR_INPUT)
			type_str = "REDIR_INPUT";
		else if (tmp->type == REDIR_OUTPUT)
			type_str = "REDIR_OUTPUT";
		else if (tmp->type == REDIR_HEREDOC)
			type_str = "REDIR_HEREDOC";
		else if (tmp->type == REDIR_APPEND)
			type_str = "REDIR_APPEND";
		else
			type_str = "NO_REDIRECTION";
		printf("Word: %s, Type: %s\n", tmp->word, type_str);
		tmp = tmp->next;
	}
}

/*
print_cmd_lst():	Prints the command list

Parameters:			t_cmd *head - the head of the command list

Return:				void

How it works:
	1. Loop through the command list
		2. Print the lexer list
	3. Free the command list
*/
void	print_cmd_lst(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp)
	{
		printf("Command %i\n", i);
		print_lexer_list(tmp->lexer);
		tmp = tmp->next;
		i++;
	}
}

/*
print_lexed():	Prints the lexed input

Parameters:		char *input - the input string

Return:			void

How it works:
	1. Split the input by pipes
	2. Loop through the strings
		3. Print the string
		4. Split the string into words
		5. Lex the words
		6. Print the lexed list
		7. Free the lexed list
	8. Free the strings

*/
void	print_lexed(char *input)
{
	char	**strings;
	char	**words;
	int		i;
	t_lexer	*lex;

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
		lex = lexer(words);
		print_lexer_list(lex);
		free_lexer_list(lex);
		free_array(words);
		i++;
	}
	free_array(strings);
}
