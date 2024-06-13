/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:13 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 16:14:16 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
print_str_array():	Prints the array of strings.

Parameters:		char **arr	-	Array of strings.

Return:			void

How it works:
	1. Iterates through the array.
	2. Prints the index and the string.
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
print_pipes_and_tokens():	Prints the pipes and tokens.

Parameters:		char *input	-	Input string.

Return:			void

How it works:
	1. Splits the input string into pipes.
	2. Iterates through the pipes.
	3. Prints the pipe.
	4. Splits the pipe into tokens.
	5. Prints the tokens.
	6. Frees the tokens.
	7. Frees the pipes.
*/
void	print_pipes_and_tokens(char *input)
{
	char	**pipes;
	char	**tokens;
	int		i;

	pipes = split_pipeline(input);
	i = 0;
	while (pipes[i] != NULL)
	{
		printf("string: %s\n", pipes[i]);
		tokens = split_tokens(pipes[i]);
		if (!tokens)
		{
			free_array(tokens);
			return ;
		}
		print_str_array(tokens);
		free_array(tokens);
		i++;
	}
	free_array(pipes);
}

/*
print_lexer_list():	Prints the lexer list.

Parameters:		t_lexer *head	-	Head of the lexer list.

Return:			void

How it works:
	1. Iterates through the lexer list.
	2. Prints the word and the type.
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
print_cmd_lst():	Prints the command list.

Parameters:		t_cmd *head	-	Head of the command list.

Return:			void

How it works:
	1. Iterates through the command list.
	2. Prints the command number.
	3. Calls the print_lexer_list function.
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
print_lexed():	Prints the lexed input.

Parameters:		char *input	-	Input string.

Return:			void

How it works:
	1. Splits the input string into pipes.
	2. Iterates through the pipes.
	3. Splits the pipe into tokens.
	4. Calls the lexer function.
	5. Calls the print_lexer_list function.
	6. Frees the tokens.
	7. Frees the pipes.
*/
void	print_lexed(char *input)
{
	char	**strings;
	char	**words;
	int		i;
	t_lexer	*lex;

	strings = split_pipeline(input);
	i = 0;
	while (strings[i] != NULL)
	{
		printf("string: %s\n", strings[i]);
		words = split_tokens(strings[i]);
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
