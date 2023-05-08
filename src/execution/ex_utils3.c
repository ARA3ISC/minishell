/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:09:41 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 00:09:58 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstrfd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	if (fd > 2)
		close(fd);
}

void close_fds(t_node *node, t_node *tmp)
{
	while(tmp && tmp->index <= node->index)
	{
		if(tmp->index == node->index)
		{
			if (tmp->inf_fd > 2)
				dup2(tmp->inf_fd, 0);
		}
		else 
		if(tmp->index + 1 == node->index)
		{
			close(tmp->fds[1]);
			if(tmp->inf_fd == 0)
				dup2(tmp->fds[0], 0);
			if (tmp->inf_fd > 2)
				dup2(tmp->inf_fd, 0);
		}
		else
		{
			close(tmp->fds[0]);
			close(tmp->fds[1]);
		}
		tmp = tmp->next;
	}
}

void close_all_fds(t_node *node, t_node *tmp)
{
	while(tmp && tmp->index <= node->index)
	{
		if (tmp->fds[0] > 2)
			close(tmp->fds[0]);
		if (tmp->fds[1] > 2)
			close(tmp->fds[1]);		
		tmp = tmp->next;
	}
}