/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:26:45 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/14 00:47:00 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**alloc_pipes(char **all_cmds)
{
	int **arr;
	int i = 0;

	arr = malloc(sizeof(int *) * cmds_count(all_cmds));
	if(!arr)
		return NULL;
	while (i < cmds_count(all_cmds))
	{
		arr[i] = malloc(sizeof(int) * 2);
		if(!arr[i])
			return NULL;
		i++;
	}
	return arr;
}

void	signal_received(char s)
{
	if (s == 'D')
	{
		printf("\nexit\n");
		exit(0);
	}
}

void	signal_C_received(int signo)
{
 	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_gb.exit_code = 1;
		// printf("%d\n", g_gb.exit_code);
	}
}
void	signal_D_received(int signo)
{
		printf("\nhahahahahaha\n");
 	if (signo == SIGQUIT)
	{
		g_gb.exit_code = 0;
	}
}
