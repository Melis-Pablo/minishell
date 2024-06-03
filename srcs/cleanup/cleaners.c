/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/03 13:13:44 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#clean_blocks():	free the blocks array

#Parameters:		char **blocks

#Return value:		void

#How it works:		
	1. Iterate through the blocks array
	2. Free each block
	3. Free the blocks array
*/
void	clean_blocks(char **blocks)
{
	int	i;

	i = 0;
	while (blocks[i])
	{
		free(blocks[i]);
		i++;
	}
	free(blocks);
}

/*
#clean_cmd_list():	free the cmd list

#Parameters:		t_cmd *cmd_list - the head of the list

#Return value:		void

#How it works:		
	1. Iterate through the list
	2. Free each node
	3. Free the list
*/
void	clean_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		clean_blocks(current->flags);
		clean_blocks(current->infile);
		clean_blocks(current->outfile);
		clean_blocks(current->append);
		free(current);
		current = next;
	}
}
