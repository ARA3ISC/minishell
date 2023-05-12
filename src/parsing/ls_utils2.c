/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:49:38 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 15:51:16 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone_env(t_env *lst)
{
	if (lst)
	{
		free(lst->name);
		free(lst->value);
		free(lst);
	}
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*p;

	p = *lst;
	if (lst)
	{
		while (*lst && p)
		{
			p = (*lst)->next;
			ft_lstdelone_env((*lst));
			*lst = p;
		}
	}
}

t_env	*ft_lstnew_env(char *name, char *value, int equal, int space)
{
	t_env	*n;

	n = malloc(sizeof(t_env));
	if (!n)
		return (NULL);
	n->name = name;
	n->value = value;
	n->equal = equal;
	n->space = space;
	n->next = NULL;
	return (n);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (*lst == NULL)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}
