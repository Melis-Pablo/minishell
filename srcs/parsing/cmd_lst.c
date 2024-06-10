/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/10 21:07:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_redir_symbols(t_lexer *head)
{
	t_lexer	*tmp;
	char	*tmp_word;
	int		chars_to_remove;

	tmp = head;
	tmp_word = NULL;
	chars_to_remove = 0;
	while (tmp)
	{
		if ((tmp->type == REDIR_INPUT && tmp->word != NULL)
			|| (tmp->type == REDIR_OUTPUT && tmp->word != NULL))
			chars_to_remove = 1;
		else if ((tmp->type == REDIR_HEREDOC && tmp->word != NULL)
			|| (tmp->type == REDIR_APPEND && tmp->word != NULL))
			chars_to_remove = 2;
		if (chars_to_remove != 0)
		{
			tmp_word = ft_strdup(tmp->word + chars_to_remove);
			free(tmp->word);
			tmp->word = tmp_word;
		}
		tmp = tmp->next;
		chars_to_remove = 0;
	}
}

// ADD ERROR HANDLING FOR <<<, ><<, >><<, etc and checks for <file<file, etc
////////////////////////////////////////
//             lexer types            //
////////////////////////////////////////
int	is_input_redirection(char *word)
{
	if (word && ft_strcmp(word, "<") == 0)
		return (1);
	if (ft_strlen(word) > 1 && word[0] == '<' )
	{
		if (word[1] == '<')
			return (0);
		return (1);
	}
	return (0);
}

int	is_output_redirection(char *word)
{
	if (word && ft_strcmp(word, ">") == 0)
		return (1);
	if (ft_strlen(word) > 1 && word[0] == '>')
	{
		if (word[1] == '>')
			return (0);
		return (1);
	}
	return (0);
}

int	is_heredoc_redirection(char *word)
{
	if (word && ft_strcmp(word, "<<") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '<' && word[1] == '<'))
		return (1);
	return (0);
}

int	is_append_redirection(char *word)
{
	if (word && ft_strcmp(word, ">>") == 0)
		return (1);
	if (ft_strlen(word) > 2 && (word[0] == '>' && word[1] == '>'))
		return (1);
	return (0);
}

void	fill_types(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_input_redirection(tmp->word))
			tmp->type = REDIR_INPUT;
		else if (is_output_redirection(tmp->word))
			tmp->type = REDIR_OUTPUT;
		else if (is_heredoc_redirection(tmp->word))
			tmp->type = REDIR_HEREDOC;
		else if (is_append_redirection(tmp->word))
			tmp->type = REDIR_APPEND;
		else
			tmp->type = NO_REDIRECTION;
		tmp = tmp->next;
	}
}

////////////////////////////////////////
//             lexer functions        //
////////////////////////////////////////
t_lexer	*add_to_list_lexer(t_lexer *head, t_lexer *new_node)
{
	t_lexer	*tmp;

	if (!head)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		return (new_node);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	new_node->next = NULL;
	return (head);
}

void	empty_redir_words(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		if ((tmp->type == REDIR_INPUT && ft_strcmp(tmp->word, "<") == 0)
			|| (tmp->type == REDIR_OUTPUT && ft_strcmp(tmp->word, ">") == 0)
			|| (tmp->type == REDIR_HEREDOC && ft_strcmp(tmp->word, "<<") == 0)
			|| (tmp->type == REDIR_APPEND && ft_strcmp(tmp->word, ">>") == 0))
		{
			free(tmp->word);
			tmp->word = NULL;
		}
		if (tmp->type == NO_REDIRECTION)
			tmp->word = ft_clean_quotes(tmp->word);
		tmp = tmp->next;
	}
}

void	free_lexer_list(t_lexer *head)
{
	t_lexer	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
}

t_lexer	*lexer(char **words)
{
	int		i;
	t_lexer	*head;
	t_lexer	*new_node;

	i = 0;
	head = NULL;
	while (words[i])
	{
		new_node = malloc(sizeof(t_lexer));
		if (!new_node)
			return (NULL);
		new_node->word = ft_strdup(words[i]);
		new_node->type = NO_REDIRECTION;
		new_node->prev = NULL;
		head = add_to_list_lexer(head, new_node);
		i++;
	}
	fill_types(head);
	empty_redir_words(head);
	clean_redir_symbols(head);
	return (head);
}


void print_lexer_list(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	char *type_str;
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
	free_lexer_list(head);
}

void	print_lexed(char *input)
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
		print_lexer_list(lexer(words));
		free_array(words);
		i++;
	}
	free_array(strings);
}

////////////////////////////////////////
//             cmd_lst functions      //
////////////////////////////////////////
t_cmd	*add_node_to_list(t_cmd *head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!head)
	{
		new_cmd->next = NULL;
		new_cmd->prev = NULL;
		return (new_cmd);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
	new_cmd->prev = tmp;
	new_cmd->next = NULL;
	return (head);
}

t_cmd	*build_node(char **words)
{
	t_lexer	*lexed_list;
	t_lexer	*head;
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	lexed_list = lexer(words);
	head = lexed_list;
	if (!lexed_list)
		return (NULL);
	// if (redirection_error(lexed_list))
	// {
	// 	free_lexer_list(head);
	// 	free(new_cmd);
	// 	return (NULL);
	// }
	//fill_node(new_cmd, lexed_list);
	free_lexer_list(head);
	return (new_cmd);
}

t_cmd	*build_struct(char *input)
{
	char	**strings;
	char	**words;
	int		i;
	t_cmd	*head;
	t_cmd	*new_cmd;

	strings = split_by_pipes(input);
	i = 0;
	head = NULL;
	while (strings[i] != NULL)
	{
		printf("string: %s\n", strings[i]);
		words = split_into_words(strings[i]);
		if (!words)
		{
			free_array(strings);
			return (NULL);
		}
		new_cmd = build_node(words);
		if (!new_cmd)
		{
			free_array(words);
			free_array(strings);
			return (NULL);
		}
		add_node_to_list(head, new_cmd);
		free_array(words);
		i++;
	}
	free_array(strings);
	return (head);
}
