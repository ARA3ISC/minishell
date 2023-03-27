/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:16:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/27 14:25:01 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg, int code)
{
	printf("%s\n", msg);
	s->error = true;
	s->exit_code = code;
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
// ls >>  '\0'
// !makhdamash (>> | ) (>> '\0')
void	check_next_cmd(char *cmd)
{
	int i = 0;
	// int count = 0;

	while (cmd[i])
	{
		if (cmd[i] != 32 && cmd[i] != '\t')
		{
			if (cmd[i] == '|' || cmd[i + 1] == '\0' || cmd[i + 1] == '|')
				printf("syntax error\n");
			else if (cmd[i] == '\0')
				return ;
		}
		i++;
	}
	// printf("%d\n", count);
	// if (count == 0 && cmd[i] == '\0')
}

void	invalid_expression(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<'))
		{
			if (cmd[i + 1] && (cmd[i + 1] == '>' || cmd[i + 1] =='<'))
				check_next_cmd(&cmd[i + 1]);
			else
				check_next_cmd(&cmd[i]);
		}
		i++;
	}
}

