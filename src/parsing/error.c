/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:16:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 15:36:50 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *msg, int code)
{
	if (msg)
		printf("%s\n", msg);
	g_gb.exit_code = code;
	return (code);
}

int	all_error(char *full_cmd)
{
	int	error;

	error = syntax_error(full_cmd);
	if (!error)
		error = check_redirection_syntax(full_cmd);
	if (!error)
		error = invalid_expression(full_cmd);
	if (!error)
		count_herdocs(full_cmd);
	return (error);
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
			return (k);
		i++;
	}
	return (k);
}

bool	check_next_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		{
			print_error("syntax error", 555);
			return (false);
		}
		else
			break ;
		i++;
	}
	return (true);
}

int	invalid_expression(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<'))
		{
			i++;
			if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
			{
				if (check_next_cmd(&cmd[i + 1]) == false)
					return (1);
			}
			else
			{
				if (cmd[i] && check_next_cmd(&cmd[i]) == false)
					return (1);
			}
		}
		if (cmd[i])
			i++;
	}
	return (0);
}
