/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:59:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:23 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_node *full_cmd)
{
	// printf(RED"cmd : hhhh\n"RESET);
	// exit(0);
	(void)full_cmd;
	t_env *tmp;
	int i;
	tmp = g_gb.my_env;
	i = 0;
	while(tmp)
	{
		ft_putstr_fd(tmp->name, full_cmd->outf_fd);
		ft_putstr_fd("=", full_cmd->outf_fd);
		if(tmp->value)
			ft_putstr_fd(tmp->value, full_cmd->outf_fd);
		// else
		// 	ft_putstr_fd("\n", full_cmd->outf_fd);
		ft_putstr_fd("\n", full_cmd->outf_fd);
		
		tmp = tmp->next;
	}
    g_gb.exit_code = 0;

}
