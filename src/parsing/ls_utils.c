/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/27 22:22:36 by eej-jama         ###   ########.fr       */
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


t_env	*ft_lstnew_env(char *name, char *value)
{
	t_env	*n;
	n = malloc(sizeof(t_env));
	if (!n)
		return (NULL);
		
	n->name = name;
	n->value = value;
	n->next = NULL;
	return (n);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	// t_env	*p;
	if (*lst == NULL)
	{
		*lst = new;
	// printf("%s : %s \n", (*lst)->name , (*lst)->value);
		
	}
	else
	{
		// p = *lst;
		while ((*lst)->next != NULL)
			(*lst) = (*lst)->next;
		(*lst)->next = new;
		// printf("%s : %s \n", (*lst)->name , (*lst)->value);
		// if(ft_lstsize(*lst) == 3)
		// 	exit(0);
	}
}