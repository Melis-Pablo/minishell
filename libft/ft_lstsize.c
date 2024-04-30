/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:55 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/03 14:41:48 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstsize():		Counts the number of nodes in a list.

#Parameters:		lst: The beginning of the list.

#Return value:		int len

#How it works:		This function counts the number of nodes in the given
					linked list by traversing the list using a temporary
					pointer and incrementing a length variable for each node
					visited. It returns the final length of the list.
*/

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	size_t	len;

	temp = lst;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
