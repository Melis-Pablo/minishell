/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:23:59 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 19:35:04 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_flags(char **words)
{
	int i = 1;
	int count = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '-' && words[i][1] != '\0') {
			count++;
		}
		i++;
	}
	return count;
}

char **get_flags(char **words)
{
	int count;
	char **flags;
	int i;
	int j;

	count = count_flags(words);
	flags = (char **)malloc(sizeof(char *) * (count + 1));
	i = 1;
	j = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '-' && words[i][1] != '\0') {
			flags[j] = words[i];
			j++;
		}
		i++;
	}
	flags[j] = NULL;
	return flags;
}

int count_infile(char **words)
{
	int i = 0;
	int count = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] != '<') {
			count++;
			if (strcmp(words[i], "<") == 0 && words[i+1] != NULL) {
				i++;
			}
		}
		i++;
	}
	return count;
}

char **get_infile(char **words)
{
	int count;
	char **infile;
	int i;
	int j;

	count = count_infile(words);
	infile = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '<' && words[i][1] != '<') {
			if (strcmp(words[i], "<") == 0 && words[i+1] != NULL) {
				infile[j] = strdup(words[i+1]);
				i++;
			} else {
				infile[j] = strdup(words[i] + 1);
			}
			j++;
		}
		i++;
	}
	infile[j] = NULL;
	return infile;
}

int count_outfile(char **words)
{
	int i = 0;
	int count = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] != '>') {
			count++;
			if (strcmp(words[i], ">") == 0 && words[i+1] != NULL) {
				i++;
			}
		}
		i++;
	}
	return count;
}

char **get_outfile(char **words)
{
	int count;
	char **outfile;
	int i;
	int j;

	count = count_outfile(words);
	outfile = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (words[i] != NULL) {
		if (words[i][0] == '>' && words[i][1] != '>') {
			if (strcmp(words[i], ">") == 0 && words[i+1] != NULL) {
				outfile[j] = strdup(words[i+1]);
				i++;
			} else {
				outfile[j] = strdup(words[i] + 1);
			}
			j++;
		}
		i++;
	}
	outfile[j] = NULL;
	return outfile;
}

int count_args(char **words)
{
    int i = 0;
    int count = 0;
    while (words[i] != NULL) {
        if (words[i][0] != '-' && words[i][0] != '<' && words[i][0] != '>') {
            count++;
        }
        i++;
    }
    return count;
}

char **get_args(char **words)
{
    int count;
    char **args;
    int i;
    int j;

    count = count_args(words);
    args = (char **)malloc(sizeof(char *) * (count + 1));
    i = 0;
    j = 0;
    while (words[i] != NULL) {
        if (words[i][0] != '-' && words[i][0] != '<' && words[i][0] != '>') {
            args[j] = words[i];
            j++;
        }
        i++;
    }
    args[j] = NULL;
    return args;
}

int count_appendfile(char **words)
{
    int i = 0;
    int count = 0;
    while (words[i] != NULL) {
        if (words[i][0] == '>' && words[i][1] == '>') {
            count++;
            if (strcmp(words[i], ">>") == 0 && words[i+1] != NULL) {
                i++;
            }
        }
        i++;
    }
    return count;
}

char **get_appendfile(char **words)
{
    int count;
    char **appendfile;
    int i;
    int j;

    count = count_appendfile(words);
    appendfile = (char **)malloc(sizeof(char *) * (count + 1));
    i = 0;
    j = 0;
    while (words[i] != NULL) {
        if (words[i][0] == '>' && words[i][1] == '>') {
            if (strcmp(words[i], ">>") == 0 && words[i+1] != NULL) {
                appendfile[j] = strdup(words[i+1]);
                i++;
            } else {
                appendfile[j] = strdup(words[i] + 2);
            }
            j++;
        }
        i++;
    }
    appendfile[j] = NULL;
    return appendfile;
}

int count_heredoc(char **words)
{
    int i = 0;
    int count = 0;
    while (words[i] != NULL) {
        if (words[i][0] == '<' && words[i][1] == '<') {
            count++;
            if (strcmp(words[i], "<<") == 0 && words[i+1] != NULL) {
                i++;
            }
        }
        i++;
    }
    return count;
}

char **get_heredoc(char **words)
{
    int count;
    char **heredoc;
    int i;
    int j;

    count = count_heredoc(words);
    heredoc = (char **)malloc(sizeof(char *) * (count + 1));
    i = 0;
    j = 0;
    while (words[i] != NULL) {
        if (words[i][0] == '<' && words[i][1] == '<') {
            if (strcmp(words[i], "<<") == 0 && words[i+1] != NULL) {
                heredoc[j] = strdup(words[i+1]);
                i++;
            } else {
                heredoc[j] = strdup(words[i] + 2);
            }
            j++;
        }
        i++;
    }
    heredoc[j] = NULL;
    return heredoc;
}

t_cmd	*add_to_lst(t_cmd *head, t_cmd *node)
{
    t_cmd	*current;

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

t_cmd *cmd_builder(char *input)
{
	t_cmd *head;
	char **str_blocks_array;
	char **words;
	t_cmd *node;
	int i;

	head = NULL;
	str_blocks_array = split_by_pipes(input);
	i = 0;
	while (str_blocks_array[i] != NULL) {
		words = split_into_words(str_blocks_array[i]);
		node = (t_cmd *)malloc(sizeof(t_cmd));
		node->cmd = words[0];
		node->flags = get_flags(words);
		node->infile = get_infile(words);
		node->outfile = get_outfile(words);
		node->append = get_appendfile(words);
		node->delimiter = get_heredoc(words);
		node->args = get_args(words);
		head = add_to_lst(head, node);
		i++;
		free(words);
	}
	return head;
}
