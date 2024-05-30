/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:53:26 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/30 15:53:52 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
