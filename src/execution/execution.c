/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/29 22:32:17 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_node *list_cmd)
{
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
