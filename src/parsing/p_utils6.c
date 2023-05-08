/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:34:50 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/07 21:49:45 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_my_env(char *exp, char *quot)
{
	t_env	*tmp;

	tmp = g_gb.my_env;
	while (tmp)
	{
		if (!ft_strcmp(exp, tmp->name))
		{
			if (tmp->space && quot[0] == '0')
			{
				printf("minishell: ambiguous redirect\n");
				return ("");
			}
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int skip_10(t_node *list_cmd, int i)
{
	if(list_cmd->cmd[i] == 39)
	{
		i++;
		while(list_cmd->cmd[i] && list_cmd->cmd[i] != 39)
		{
			list_cmd->new_cmd = ft_strjoin_char(list_cmd->new_cmd, list_cmd->cmd[i]);
			i++;
		}
		i++;
	}
	if(list_cmd->cmd[i] == 34)
		i++;

	return (i);
}

int replace_var(t_node *list_cmd, int i, int k, int j)
{
	char *var;

	var = NULL;
	if(list_cmd->cmd[i + 1] == '?')
	{
		k = i + 1;
		var = ft_itoa(g_gb.exit_code);
		i = i + 2;
	}
	else
	{
		var = get_from_my_env(list_cmd->exp_var[j], "3");
		i = i + ft_strlen(list_cmd->exp_var[j]) + 1;
	}
	if (var)
	{
		list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, var);
		if (list_cmd->cmd[k] && list_cmd->cmd[k] == '?')
			free(var);
	}
	else
		list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, "\n");
	// if(var)
	// 	free(var);
	return i;
}

void	expanding(t_node *list_cmd)
{
	int i;
	int k;
	int j;

	while (list_cmd)
	{
		j = 0;
		list_cmd->new_cmd = NULL;
		i = 0;
		while (list_cmd->cmd[i])
		{
			k = 0;
			i = skip_10(list_cmd, i);
			if(list_cmd->cmd[i] && list_cmd->cmd[i + 1] && list_cmd->cmd[i] == '$' && (list_cmd->cmd[i + 1] == '?'
					|| ft_isalnum(list_cmd->cmd[i + 1])))
			{
				i = replace_var(list_cmd, i, k, j);
				j++;
				continue;
			}
			if(list_cmd->cmd[i])
				list_cmd->new_cmd = ft_strjoin_char(list_cmd->new_cmd, list_cmd->cmd[i++]);
		}
		list_cmd = list_cmd->next;
	}
}
