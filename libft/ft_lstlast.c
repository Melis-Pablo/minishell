/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:48 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/03 14:57:22 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstlast():		Returns the last node of the list.

#Parameters:		lst: The beginning of the list.

#Return value:		last node of the list.

#How it works:		function traverses the given linked list by following the
					"next" pointer of each node until the last node is reached.
					It returns a pointer to the last node of the list. If the
					list is empty, it returns NULL.
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst->next;
	return (lst);
}
