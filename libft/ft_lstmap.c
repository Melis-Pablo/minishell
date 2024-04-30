/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:51 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/10 21:12:53 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** st_nevermind() - Frees all the memory allocated for the new list and returns
**                  NULL.
**
** @delete_this: A pointer to the first link of the new list.
** @del: The function to delete the content of a link, if necessary.
**
** Returns: NULL.
**
** This function frees all the memory allocated for the new list and returns
** NULL. It is used to handle the case where an allocation fails while
** creating a new link for the list.
*/

static t_list	*st_nevermind(t_list **delete_this, void (*del)(void *))
{
	ft_lstclear(delete_this, del);
	return (NULL);
}

/*
** st_null_last_next() - Sets the 'next' pointer of the last link in the new
**                       list to NULL.
**
** @last: A pointer to the last link in the new list.
**
** Returns: None.
**
** This function sets the 'next' pointer of the last link in the new list to
** NULL. It is used to ensure that the new list is properly terminated.
*/

static void	st_null_last_next(t_list *last)
{
	if (last)
	{
		last->next = NULL;
	}
}

/*
** ft_lstmap() - Iterates the list ’lst’ and applies the function ’f’ on the
**               content of each node. Creates a new list resulting of the
**               successive applications of the function ’f’. The ’del’
**               function is used to delete the content of a node if needed.
**
** @lst: A pointer to the first link of a list.
** @f: The function to apply to the content of each link.
** @del: The function to delete the content of a link, if necessary.
**
** Returns: A pointer to the first link of the new list.
**
** This function creates a new list resulting from the application of the
** function 'f' to the content of each link in the list 'lst'. The content of
** each link in the new list is set to the result of the function 'f' applied
** to the corresponding content in the old list. The 'del' function is used to
** delete the content of a link if necessary. If any allocation fails, the
** function frees all the memory allocated and returns NULL.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*original_item;
	t_list	**next;
	t_list	*new_previous;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	next = &new_list;
	original_item = lst;
	new_previous = NULL;
	while (original_item)
	{
		*next = malloc(sizeof(t_list));
		if (*next == NULL)
			return (st_nevermind(&new_list, del));
		(*next)->content = f(original_item->content);
		if (new_previous)
			new_previous->next = (*next);
		new_previous = *next;
		original_item = original_item->next;
		next = &((*next)->next);
	}
	st_null_last_next(new_previous);
	return (new_list);
}
