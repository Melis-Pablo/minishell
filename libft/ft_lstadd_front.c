/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:36 by pmelis            #+#    #+#             */
/*   Updated: 2023/12/23 23:23:22 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstadd_front():	Adds the node ’new’ at the beginning of the list.

#Parameters:		lst: The address of a pointer to the first link of a list.
					new: The address of a pointer to the node to be added to
						the list.

#Return value:		void

#How it works:		This function adds the given node to the front of the 
					given linked list by updating the "next" pointer of the
					new node to point to the current head of the list, and
					then updating the "lst" pointer to point to the new node.
*/

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	new_node->next = *lst;
	*lst = new_node;
}
