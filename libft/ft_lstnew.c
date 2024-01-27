/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:53 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/03 13:02:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
#ft_lstnew():	Allocates and returns a new node with the given content.

#Parameters:	void *content (The content to create the node with.)

#Return value:	*newnode, or NULL if allocation fails.

#How it works:	This function creates a new node for a linked list and stores
				the given content in it. The "next" pointer of the new node is
				initialized to NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
