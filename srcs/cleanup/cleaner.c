/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:55:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/14 15:07:19 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#clear_lexer():	clears lexer struct (free's it)

#Parameters:	t_lexer *head

#Return value:	void

#How it works:	1. declare t_lexer *tmp
				2. While list still going
					a. set tmp = head
					b. set head = next
					c. free tmp str
					d. free tmp node.
*/
void	clear_lexer(t_lexer *head)
{
	t_lexer	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}
