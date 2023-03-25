/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:48:17 by eej-jama          #+#    #+#             */
/*   Updated: 2023/03/24 22:17:18 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstmap(t_node *lst, void *(*f)(void *), void (*del)(void *))
{
	t_node	*head;
	t_node	*i;
	t_node	*new;

	if (!lst)
		return (NULL);
	head = 0 ;
	i = lst;
	while (i)
	{
		new = malloc(sizeof(t_node));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		new->content = f(i->content);
		new->next = NULL;
		ft_lstadd_back(&head, new);
		i = i -> next;
	}
	return (head);
}
