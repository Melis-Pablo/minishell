/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:53:45 by pmelis            #+#    #+#             */
/*   Updated: 2023/03/08 21:20:25 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#ft_lstiter():		Applies the function `f` to each node in the list `lst`.

#Parameters:		t_list *lst
					void (*f)(void *)

#Return value:		void

#How it works:		check if f is null to terminate function. loop trough the
					lst until null, calls the function with the content of the
					current node and then move to the next node.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
