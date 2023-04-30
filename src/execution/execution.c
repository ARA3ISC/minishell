/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/30 14:32:28 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void index_list(t_node *list)
{
	int i;

	i = 0;
	while(list)
	{
		list->index = i;
		i++;
		list = list->next;
	}
}

void	execution(t_node *list_cmd)
{
	index_list(list_cmd);
	// int i = 0;
	// while(list_cmd)
	// {
	// 	printf("index : %d", list_cmd->index);
	// 	list_cmd = list_cmd->next;
	// }
	// exit(10);
	if (ft_lstsize(list_cmd) == 1 && is_builtin(list_cmd))
	{
		// printf("builtin\n");
		// execute_one_built_cmd(list_cmd);
	}
	else
	{
		execute_list_of_cmds(list_cmd);
	}
}
