/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:16:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/28 14:15:46 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg, int code)
{
	printf("%s\n", msg);
	if(s)
	{
		s->error = true;
		s->exit_code = code;
		printf("exit code : %d\n", s->exit_code);
	}
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

bool	check_next_cmd(char *cmd)
{
	int i = 0;

	while (cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
		i++;
	// printf("%s\n", &cmd[i]);
	// exit(1);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		{
			print_error("syntax err", 258);
			return false;
		}
		else
			break ;
		i++;
	}
	return true;
}

void	invalid_expression(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<'))
		{
			if (cmd[i + 1] && (cmd[i + 1] == '>' || cmd[i + 1] =='<'))
			{
				if (check_next_cmd(&cmd[i + 2]) == false)
					return ;
			}
			else
			{
				if (check_next_cmd(&cmd[i + 1]) == false)
					return ;
			}
		}
		i++;
	}
}

