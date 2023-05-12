/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:36:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 15:50:21 by eej-jama         ###   ########.fr       */
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
	return (n);
}

void	free_big_one(char **tab)
{
	free(tab);
}

void	free_cmd_dt(t_node *lst)
{
	if (lst->op_count > 0)
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
	if (lst->herdocs_count > 0)
		free_2d_table(lst->cmd_dt->eofs);
	else
		free_big_one(lst->cmd_dt->eofs);
	free(lst->cmd_dt);
}

void	free_exp(t_node *lst)
{
	if (lst->var_count > 0)
		free_2d_table(lst->exp_var);
	else
		free_big_one(lst->exp_var);
}
