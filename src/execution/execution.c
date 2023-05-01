/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/01 19:11:42 by eej-jama         ###   ########.fr       */
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
	int fk;
	index_list(list_cmd);
	if (ft_lstsize(list_cmd) == 1 && is_builtin(list_cmd))
	{
		fk = fork();
		if (fk == 0)
		{
			builtins(list_cmd);
			exit(0);
		}
		while (wait(NULL) != -1) ;
	}
	else
	{
		
		execute_list_of_cmds(list_cmd);
	}
}
