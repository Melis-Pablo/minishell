/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:23:59 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/04 14:44:57 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_flags(char **words)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**get_flags(char **words)
{
	int		count;
	char	**flags;
	int		i;
	int		j;

	count = count_flags(words);
	flags = (char **)malloc(sizeof(char *) * (count + 1));
	i = 1;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '-' && words[i][1] != '\0')
		{
			flags[j] = words[i];
			j++;
		}
		i++;
	}
	flags[j] = NULL;
	return (flags);
}

int	count_infile(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '<' && words[i][1] != '<')
		{
			count++;
			if (strcmp(words[i], "<") == 0 && words[i + 1] != NULL)
				i++;
		}
		i++;
	}
	return (count);
}

char	**get_infile(char **words)
{
	int		count;
	char	**infile;
	int		i;
	int		j;

	count = count_infile(words);
	infile = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '<' && words[i][1] != '<')
		{
			if (strcmp(words[i], "<") == 0 && words[i + 1] != NULL)
			{
				infile[j] = strdup(words[i + 1]);
				i++;
			}
			else
				infile[j] = strdup(words[i] + 1);
			j++;
		}
		i++;
	}
	infile[j] = NULL;
	return (infile);
}

int	count_outfile(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '>' && words[i][1] != '>')
		{
			count++;
			if (strcmp(words[i], ">") == 0 && words[i + 1] != NULL)
				i++;
		}
		i++;
	}
	return (count);
}

char **get_outfile(char **words)
{
	int		count;
	char	**outfile;
	int		i;
	int		j;

	count = count_outfile(words);
	outfile = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '>' && words[i][1] != '>')
		{
			if (strcmp(words[i], ">") == 0 && words[i + 1] != NULL)
			{
				outfile[j] = strdup(words[i + 1]);
				i++;
			}
			else
				outfile[j] = strdup(words[i] + 1);
			j++;
		}
		i++;
	}
	outfile[j] = NULL;
	return (outfile);
}

int	count_args(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] != '-' && words[i][0] != '<' && words[i][0] != '>')
			count++;
		i++;
	}
	return (count);
}

char **get_args(char **words)
{
	int		count;
	char	**args;
	int		i;
	int		j;

	count = count_args(words);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] != '-' && words[i][0] != '<' && words[i][0] != '>')
		{
			args[j] = words[i];
			j++;
		}
		i++;
	}
	args[j] = NULL;
	return (args);
}

int	count_appendfile(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '>' && words[i][1] == '>')
		{
			count++;
			if (strcmp(words[i], ">>") == 0 && words[i + 1] != NULL)
				i++;
		}
		i++;
	}
	return (count);
}

char **get_appendfile(char **words)
{
	int		count;
	char	**appendfile;
	int		i;
	int		j;

	count = count_appendfile(words);
	appendfile = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '>' && words[i][1] == '>')
		{
			if (strcmp(words[i], ">>") == 0 && words[i + 1] != NULL)
			{
				appendfile[j] = strdup(words[i + 1]);
				i++;
			}
			else
				appendfile[j] = strdup(words[i] + 2);
			j++;
		}
		i++;
	}
	appendfile[j] = NULL;
	return (appendfile);
}

int	count_heredoc(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '<' && words[i][1] == '<')
		{
			count++;
			if (strcmp(words[i], "<<") == 0 && words[i + 1] != NULL)
				i++;
		}
		i++;
	}
	return (count);
}

char **get_heredoc(char **words)
{
	int		count;
	char	**heredoc;
	int		i;
	int		j;

	count = count_heredoc(words);
	heredoc = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '<' && words[i][1] == '<')
		{
			if (strcmp(words[i], "<<") == 0 && words[i + 1] != NULL)
			{
				heredoc[j] = strdup(words[i + 1]);
				i++;
			}
			else
				heredoc[j] = strdup(words[i] + 2);
			j++;
		}
		i++;
	}
	heredoc[j] = NULL;
	return (heredoc);
}


t_cmd	*add_to_lst(t_cmd *head, t_cmd *node)
{
	t_cmd	*current;

	current = NULL;
	if (head == NULL)
		head = node;
	else
	{
		current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
	return (head);
}

t_cmd	*cmd_builder(char *input)
{
	t_cmd	*node;
	char	**words;
	int		i;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->cmd = NULL;
	node->flags = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = NULL;
	node->delimiter = NULL;
	node->args = NULL;
	node->next = NULL;
	node->prev = NULL;
	words = split_into_words(input);
	node->cmd = words[0];
	node->flags = get_flags(words);
	node->infile = get_infile(words);
	node->outfile = get_outfile(words);
	node->append = get_appendfile(words);
	node->delimiter = get_heredoc(words);
	node->args = get_args(words);
	free(words);
	return (node);
}

t_cmd *build_cmd_list(char *input)
{
	char		**inputs;
	int			i;
	t_cmd		*head;
	t_cmd		*current;
	t_cmd		*node;

	i = 0;
	head = NULL;
	current = NULL;
	inputs = split_by_pipes(input);
	while (inputs[i] != NULL)
	{
		node = cmd_builder(inputs[i]);
		if (head == NULL)
		{
			head = node;
			current = node;
		}
		else
		{
			current->next = node;
			current = node;
		}
		i++;
	}
	free_array(inputs);
	return (head);
}
