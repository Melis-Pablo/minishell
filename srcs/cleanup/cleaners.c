/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/30 23:57:53 by pmelis           ###   ########.fr       */
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
