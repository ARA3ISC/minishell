/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/29 22:38:11 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*p;

	if (*lst == NULL)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_node	*ft_lstnew(char *_cmd, int *fds)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->cmd = _cmd;
	n->fds = fds;
	n->next = NULL;
	return (n);
}

void	ft_lstdelone(t_node *lst)
{
	if (lst)
	{
		free(lst->cmd);
		free(lst->fds);
		free(lst);
	}
}

void	ft_lstclear(t_node **lst)
{
	t_node	*p;

	if (lst)
	{
		while (*lst)
		{
			p = (*lst)->next;
			ft_lstdelone((*lst));
			*lst = p;
		}
	}
}
