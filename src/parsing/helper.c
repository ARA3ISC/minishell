/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:28 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/30 16:29:04 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmds_count(char **cmds)
{
	int i = 0;
	while (cmds[i])
		i++;
	return i;
}

char    *get_pwd(char **env)
{
	int i = 0;

	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
			return env[i];
		i++;
	}
	return (NULL);
}

int	count_op(char *cmd)
{
	int i = 0;
	int count = 0;

	// exit(10);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	count_pipes(char *cmd)
{


	int i = 0;
	int count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	get_herdocs_count(char *single_cmd)
{
	int i = 0;
	int count = 0;
	while (single_cmd[i])
	{
		if (single_cmd[i] && single_cmd[i] == '<' && single_cmd[i + 1] == '<')
		{
			count++;
			i++;
		}
		if (single_cmd[i])
			i++;
	}
	return count;
}

void	get_number_of_tokens(char *full_cmd, t_node *list_cmd)
{
	while (list_cmd)
	{
		g_gb.infos = malloc(sizeof(t_info));
		if(!g_gb.infos)
			return ;
		list_cmd->op_count = count_op(list_cmd->cmd);
		list_cmd->herdocs_count = get_herdocs_count(list_cmd->cmd);

		g_gb.infos->pipe_count = count_pipes(full_cmd);
		g_gb.infos->cmd_count = g_gb.infos->pipe_count + 1;
		list_cmd = list_cmd->next;
	}
}
