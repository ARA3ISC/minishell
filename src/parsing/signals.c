/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:26:45 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/29 21:50:12 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**alloc_pipes(char **all_cmds)
{
	int **arr;
	int i = 0;

	arr = malloc(sizeof(int *) * cmds_count(all_cmds));

	while (i < cmds_count(all_cmds))
	{
		arr[i] = malloc(sizeof(int) * 2);
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
	char **tmp = malloc(2 * sizeof(char *));
 	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		if(s)
			s->exit_code = 1;
		else
		{
			ft_lstadd_back(&s, ft_lstnew(" ", *alloc_pipes(tmp)));
			s->exit_code = 1;
		}

	}
}
