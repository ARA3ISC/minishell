/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:48:57 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:12:01 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_flags(t_node *lst)
{
	if (lst->cmd_flags)
		free_2d_table(lst->cmd_flags);
}

void	ft_lstdelone(t_node *lst)
{
	if (lst)
	{
		free(lst->cmd);
		free_cmd_dt(lst);
		free_exp(lst);
		free(lst->new_cmd);
		free_flags(lst);
		free(lst);
	}
}

int	ft_lstsize(t_node *lst)
{
	int	len;

	len = 0;
	if (lst)
	{
		while (lst)
		{
			len++;
			lst = lst->next;
		}
	}
	return (len);
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
