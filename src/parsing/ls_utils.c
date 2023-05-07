/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/07 11:22:54 by eej-jama         ###   ########.fr       */
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
	n->only_heredoc = false;
	n->next = NULL;
	
	// printf("cmd %s\n", n->next->cmd);

	return (n);
}

void free_big_one(char **tab)
{
	free(tab);
}

void free_cmd_dt(t_node *lst)
{
	if(lst->op_count > 0)
	{

		free_2d_table(lst->cmd_dt->file);
		free_2d_table(lst->cmd_dt->op);
		free_2d_table(lst->cmd_dt->to_open);
		free_2d_table(lst->cmd_dt->coted);
	}
	else
	{
		free_big_one(lst->cmd_dt->op);
		free_big_one(lst->cmd_dt->file);
		free_big_one(lst->cmd_dt->to_open);
		free_big_one(lst->cmd_dt->coted);
	}
	if(lst->herdocs_count > 0)
		free_2d_table(lst->cmd_dt->eofs);
	else
		free_big_one(lst->cmd_dt->eofs);
	free(lst->cmd_dt);
		
}


void free_exp(t_node *lst)
{
	if(lst->var_count > 0)
	{
		free_2d_table(lst->exp_var);
	}
	else
	{
		free_big_one(lst->exp_var);
	}	
}

void free_flags(t_node *lst)
{
	if(lst->cmd_flags)
	{
		free_2d_table(lst->cmd_flags);
	}
	// else
	// {
	// 	free_big_one(lst->cmd_flags);
	// }	
}

void	ft_lstdelone(t_node *lst)
{
	if (lst)
	{
		
		free(lst->cmd);
		// free(lst->cmd_dt->file[0]);
		free_cmd_dt(lst);
		free_exp(lst);
		free(lst->new_cmd);
		free_flags(lst);
		
		// free(lst->cmd_dt->file);
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
	p = *lst;
	if (lst)
	{
		while (*lst && p)
		{
			p = (*lst)->next;
			ft_lstdelone((*lst));
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
    	// printf("name : |%s|\nvalue : |%s|\n", new->name, new->value);
		
		p = *lst;
		while (p->next)
		{
			// printf("name : %s\n", p->name);
			p = p->next;
		}
		// printf("name : %s\n", p->name);
		
		p->next = new;
		// printf("name : %s\n", p->next->name);

		// printf("%s : %s \n", (*lst)->name , (*lst)->value);
		// if(ft_lstsize(*lst) == 3)
		// 	exit(0);
	}
}
