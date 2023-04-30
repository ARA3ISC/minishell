/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:59:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/29 22:17:06 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(char *full_cmd)
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
		printf("%s=", tmp->name);
		if(tmp->value)
			printf("%s\n", tmp->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
}
