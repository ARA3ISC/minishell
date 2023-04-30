/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/30 13:38:25 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	// if((*lst)->cmd)
	// 	printf("cmd %s\n", (*lst)->cmd);
	t_node	*p;

	if (*lst == NULL)
	{
		
		*lst = new;
		// printf("cmd %s\n", (*lst)->cmd);
	}
	else
	{

		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
	// printf("cmd %s\n", (*lst)->cmd);
	// if((*lst)->next)
	// 	printf("cmd %s\n", (*lst)->next->cmd);
	// printf("cmd %s\n", (*lst)->next->next->cmd);
}

t_node	*ft_lstnew(char *_cmd)
{
	
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->cmd = _cmd;
	n->inf_fd = 0;
	n->outf_fd = 1;
	n->next = NULL;
	
	// printf("cmd %s\n", n->next->cmd);

	return (n);
}

void	ft_lstdelone(t_node *lst)
{
	if (lst)
	{
		free(lst->cmd);
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
	t_env	*p;
	if (*lst == NULL)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
		// printf("%s : %s \n", (*lst)->name , (*lst)->value);
		// if(ft_lstsize(*lst) == 3)
		// 	exit(0);
	}
}
