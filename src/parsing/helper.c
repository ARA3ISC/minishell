/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:28 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 15:47:27 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmds_count(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

char	*get_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	skip_must(char *cmd, int i)
{
	if (cmd[i] == 39)
	{
		i++;
		while (cmd[i] && cmd[i] != 39)
			i++;
		i++;
	}
	else if (cmd[i] && cmd[i] == 34)
	{
		i++;
		while (cmd[i] && cmd[i] != 34)
			i++;
		i++;
	}
	else
		i++;
	return (i);
}

int	count_op(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			count++;
			if (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
				i++;
		}
		i = skip_must(cmd, i);
	}
	return (count);
}

int	skip_d(char *cmd, int i)
{
	if (cmd[i] == 39)
	{
		i++;
		while (cmd[i] && cmd[i] != 39)
			i++;
		i++;
	}
	else if (cmd[i] && cmd[i] == 34)
	{
		i++;
		while (cmd[i] && cmd[i] != 34)
			i++;
		i++;
	}
	else
		i++;
	return (i);
}
