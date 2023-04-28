/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/28 15:11:41 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_node *list_cmd)
{
	if (ft_lstsize(list_cmd) == 1 && is_builtin(list_cmd))
	{
		printf("builtin\n");
		// execute_one_built_cmd(list_cmd);
	}
	else
	{
		// int i;
		// while (list_cmd)
		// {
		// 	i = 0;
		// 	// printf("infile :%d\n", list_cmd->inf_fd);
		// 	// printf("outfile :%d\n", list_cmd->outf_fd);
		// 	while (list_cmd->cmd_dt->file[i])
		// 	{
		// 		printf("file[%d] :%s\n", i, list_cmd->cmd_dt->file[i]);
		// 		i++;
		// 	}
		// 	printf("-----\n");
		// 	list_cmd = list_cmd->next;
		// }
		// exit(0);
		execute_list_of_cmds(list_cmd);
	}
}
