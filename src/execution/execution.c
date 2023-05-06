/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/06 09:00:33 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void index_list(t_node *list)
{
	int i;
	i = 0;
	
	// if ((*list)->cmd_flags[0] == NULL)
	// {
	// 	printf("dkhel");
	// 	return;
	// }
	// 	printf("--> %s\n", list->cmd_flags[0]);
	// exit(10);
	// printf("cmd : |%s|\n", list->cmd);
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
	// printf("new cmd : |%s|\n", list_cmd->new_cmd);
	if (list_cmd->new_cmd && ft_lstsize(list_cmd) == 1 && is_builtin(list_cmd))
	{
		g_gb.error = open_files(list_cmd);
		if (g_gb.error != 0)
			builtins(list_cmd);
	}
	else
	{
					
		
		execute_list_of_cmds(list_cmd);
		
		
	}
	
}
