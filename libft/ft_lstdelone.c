/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:42 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 21:09:44 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_lstdelone():	Deletes a single node from a linked list

#Parameters:		lst:  The node to free.
					del:  The address of the function used to delete the
							content.

#Return value:		void

#How it works:		This function frees the memory occupied by a single node in
					the linked list. The del() function is called to free the
					memory occupied by the content of the node. After the
					content has been freed, the memory occupied by the node
					itself is freed.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del != NULL && lst != NULL)
	{
		(*del)(lst->content);
		free(lst);
	}
}
