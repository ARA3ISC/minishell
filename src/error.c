/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:16:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/26 15:20:04 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	printf("%s\n", msg);
}

void	print_error_and_break(char *msg)
{
	printf("%s\n", msg);
}

int	check_whitespaces(char **all_cmds)
{
	int	k;
	int	i;
	int	j;


	i = 0;
	while (all_cmds[i])
	{
		k = 1;
		j = 0;
		while (all_cmds[i][j])
		{
			if (all_cmds[i][j] != 32 && all_cmds[i][j] != '\t')
				k = 0;
			j++;
		}
		if (k)
			return k;
		i++;
	}
	return (k);
}


