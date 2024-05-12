/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/12 18:29:43 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *parser(t_lexer *head_node)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;

    char *input = head_node->str;
    int start = 0;
    int end = 0;
    int index = 0;

    while (input[end] != '\0')
    {
        if (input[end] == ' ' || input[end] == '\t')
        {
            if (start != end)
            {
                char *token = malloc(end - start + 1);
                if (!token)
                {
                    // handle malloc failure
                }
                strncpy(token, &input[start], end - start);
                token[end - start] = '\0';

                // add token to cmd
                cmd->tokens[index++] = token;
            }
            start = end + 1;
        }
        end++;
    }

    if (start != end)
    {
        char *token = malloc(end - start + 1);
        if (!token)
        {
            // handle malloc failure
        }
        strncpy(token, &input[start], end - start);
        token[end - start] = '\0';

        // add token to cmd
        cmd->tokens[index++] = token;
    }

    cmd->tokens[index] = NULL; // null terminate the tokens array

    return cmd;
}
