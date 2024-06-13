/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:58:13 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 13:11:03 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
