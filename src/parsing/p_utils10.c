/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:47:02 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 16:05:19 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '|')
			count++;
		i = skip_d(cmd, i);
	}
	return (count);
}

int	get_herdocs_count(char *single_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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
	return (count);
}

void	get_number_of_tokens(char *full_cmd, t_node *list_cmd)
{
	g_gb.infos = malloc(sizeof(t_info));
	if (!g_gb.infos)
		return ;
	while (list_cmd)
	{
		list_cmd->op_count = count_op(list_cmd->cmd);
		list_cmd->herdocs_count = get_herdocs_count(list_cmd->cmd);
		g_gb.infos->pipe_count = count_pipes(full_cmd);
		g_gb.infos->cmd_count = g_gb.infos->pipe_count + 1;
		list_cmd = list_cmd->next;
	}
	g_gb.infos->pipe_count = count_pipes(full_cmd);
	g_gb.infos->cmd_count = g_gb.infos->pipe_count + 1;
}
