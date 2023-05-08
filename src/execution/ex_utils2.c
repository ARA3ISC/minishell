/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:06:58 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 00:08:41 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    error_case(t_node *list_cmd)
{
    if ((!list_cmd->cmd_flags || !ft_strlen(list_cmd->cmd_flags[0])) && !list_cmd->only_heredoc)
		cmd_not_found(NULL);
	if (list_cmd->cmd_flags && list_cmd->cmd_flags[0])
		cmd_not_found(list_cmd->cmd_flags[0]);
	else if(!list_cmd->cmd_flags)
		cmd_not_found("");
	else
		exit(0);
}