/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:56:55 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/06 17:39:56 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer *new_lexer_node(char *str, t_token_type token, int index) {
    t_lexer *node = malloc(sizeof(t_lexer));
    if (!node) return NULL;
    node->str = str;
    node->token = token;
    node->next = NULL;
    node->prev = NULL;
	node->index = index;
    return node;
}

t_lexer *lexer(char *input)
{
    t_lexer *head = NULL;
    t_lexer *current = NULL;
    char *token;
    t_token_type token_type;
	int index = 0;

    while (*input) {
        if (*input == '>') {
            token = NULL;
            token_type = GREATER;
            input++;
        } else if (*input == '<') {
            token = NULL;
            token_type = LESS;
            input++;
        } else if (*input == '|') {
            token = NULL;
            token_type = PIPE;
            input++;
        } else {
            // Extract string until next token or end of input
            char *start = input;
            while (*input && *input != '>' && *input != '<' && *input != '|') {
                if (*input == '\'' || *input == '\"') {
                    // Skip quoted string
                    char quote = *input++;
                    while (*input && *input != quote) input++;
                    if (*input) input++;
                } else {
                    input++;
                }
            }
            token = strndup(start, input - start);
            token_type = NONE;
        }

        t_lexer *node = new_lexer_node(token, token_type, index++);
        if (!node) {
            // Handle memory allocation error
            return NULL;
        }

        if (!head) {
            head = node;
        } else {
            current->next = node;
            node->prev = current;
        }
        current = node;
    }

    return head;
}
