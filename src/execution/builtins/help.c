/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:24:27 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:33:46 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_export(t_node *full_cmd)
{
	t_env	*tmp;

	tmp = g_gb.my_export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", full_cmd->outf_fd);
		ft_putstr_fd(tmp->name, full_cmd->outf_fd);
		if (tmp->equal)
		{
			ft_putstr_fd("=\"", full_cmd->outf_fd);
			if (tmp->value)
				ft_putstr_fd(tmp->value, full_cmd->outf_fd);
			ft_putstr_fd("\"\n", full_cmd->outf_fd);
		}
		else
			ft_putstr_fd("\n", full_cmd->outf_fd);
		tmp = tmp->next;
	}
}

int	name_is_exist_in_env(char *name)
{
	t_env	*tmp;

	tmp = g_gb.my_env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	name_is_exist_in_export(char *name)
{
	t_env	*tmp;

	tmp = g_gb.my_export;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	skip_of(char *cmd, int i)
{
	i++;
	if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		i++;
	while (cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
		i++;
	if (cmd[i] && cmd[i] == 34)
	{
		i++;
		while (cmd[i] && cmd[i] != 34)
			i++;
		i++;
	}
	else if (cmd[i] && cmd[i] == 39)
	{
		i++;
		while (cmd[i] && cmd[i] != 39)
			i++;
		i++;
	}
	else
		while (cmd[i] && cmd[i] != 32 && cmd[i] != '\t')
			i++;
	return (i);
}

int	get_name_from_double_quot(char *cmd, char **name, int i, t_node *full_cmd)
{
	i++;
	while (cmd[i] && cmd[i] != 34)
	{
		if ((cmd[i] < 65 && cmd[i] > 31) || cmd[i] == '\0')
		{
			ft_putstr_fd("minishell: export: not a valid identifier",
				full_cmd->outf_fd);
			ft_putstr_fd("\n", full_cmd->outf_fd);
			return (0);
		}
		*name = ft_strjoin_char(*name, cmd[i++]);
	}
	i++;
	return (i);
}
