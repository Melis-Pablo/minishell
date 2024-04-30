/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:32 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/23 23:23:02 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstadd_back():	Adds the node ’new’ at the end of the list.

#Parameters:		lst:  The address of a pointer to the first link of a list.
					new:  The address of a pointer to the node to be added to
						the list.

#Return value:		void

#How it works:		This function adds a new node to the end of the given linked
					list by traversing the list to find the last node, and then
					setting its "next" pointer to point to the new node. If the
					list is empty, the "lst" pointer is updated to point to the
					new node. If the new node pointer is NULL, the function
					returns without modifying the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new_node;
}
