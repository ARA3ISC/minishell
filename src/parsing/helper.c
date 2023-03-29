/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:28 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/29 14:30:13 by maneddam         ###   ########.fr       */
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

void	get_number_of_tokens(char *full_cmd)
{
	t_node *tmp;

	tmp = s;
	while (s)
	{
		s->infos = malloc(sizeof(t_info));
		s->infos->op_count = count_op(s->cmd);

		s->infos->pipe_count = count_pipes(full_cmd);
		s->infos->cmd_count = s->infos->pipe_count + 1;
		s = s->next;
	}
	s = tmp;
}
