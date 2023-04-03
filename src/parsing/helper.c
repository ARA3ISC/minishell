/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:28 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/30 17:38:50 by eej-jama         ###   ########.fr       */
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

t_node *get_number_of_tokens(char *full_cmd, t_node *list_cmd)
{
	t_node *tmp;
	
	tmp = list_cmd;;
	while (tmp)
	{
		tmp->infos = malloc(sizeof(t_info));
		if(!tmp->infos)
			return NULL;
		tmp->infos->op_count = count_op(tmp->cmd);
	

		tmp->infos->pipe_count = count_pipes(full_cmd);
		tmp->infos->cmd_count = tmp->infos->pipe_count + 1;
		tmp = tmp->next;
	}
	return list_cmd;
}
