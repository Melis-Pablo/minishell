/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:37 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 21:15:17 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstclear():		frees the memory of a linked list by iterating through each
					node and deleting its content using the provided function.

#Parameters:		lst:  The address of a pointer to a node.
					del:  The address of the function used to delete the
						contentof the node.

#Return value:		void

#How it works:		This function takes a pointer to the first node of a linked
					list and a function pointer to a function that deletes the
					content of each node. It then loops through the linked
					list, deleting the content of each node using the provided
					function and moving on to the next node until the end of
					the list is reached. Finally, it sets the pointer to the
					first node to NULL.

*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
