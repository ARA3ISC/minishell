/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/13 18:39:05 by maneddam         ###   ########.fr       */
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

int	ft_lstsize(t_node *lst)
{
	int len = 0;
	if (lst)
	{
		while (lst)
		{
			len++;
			lst = lst->next;
		}
	}
	return len;
}

void	ft_lstclear(t_node **lst)
{
	t_node	*p;

	if (lst)
	{
		while (*lst && p)
		{
			// printf ("lst->cmd = |%s|\n", (*lst)->cmd);
			p = (*lst)->next;
			ft_lstdelone((*lst));
			*lst = p;
		}
	}
}

