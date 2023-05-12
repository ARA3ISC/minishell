/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:33:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 21:05:07 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_value_too(char *cmd, int i, char **value)
{
	i++;
	while (cmd[i] && cmd[i] != 32)
	{
		if (cmd[i] == 34)
		{
			i++;
			while (cmd[i] && cmd[i] != 34)
				*value = ft_strjoin_char(*value, cmd[i++]);
			i++;
		}
		else if (cmd[i] == 39)
		{
			i++;
			while (cmd[i] && cmd[i] != 39)
				*value = ft_strjoin_char(*value, cmd[i++]);
			i++;
		}
		else
			*value = ft_strjoin_char(*value, cmd[i++]);
	}
	return (i);
}

int	add_to_export(char *cmd, int i, t_node *full_cmd, char *name)
{
	t_env	*tmp2;

	tmp2 = g_gb.my_export;
	while (cmd[i] && cmd[i] == 32)
		i++;
	if (cmd[i] && !ft_isalnum(cmd[i]))
	{
		ft_putstr_fd("not a valid identifier", full_cmd->outf_fd);
		ft_putstr_fd("\n", full_cmd->outf_fd);
		return (0);
	}
	if (!name_is_exist_in_export(expend_herdocc(name)))
		ft_lstadd_back_env(&tmp2, ft_lstnew_env(expend_herdocc(name), "", 0,
				existe_spaces("")));
	free(name);
	if (cmd[i])
		i++;
	return (i);
}

void	add_to_env_exp(char *name, char *value, int plus)
{
	t_env	*tmp;

	tmp = g_gb.my_env;
	if (name_is_exist_in_env(name))
	{
		while (tmp)
		{
			if (!ft_strcmp(name, tmp->name))
			{
				if (plus)
					tmp->value = ft_strjoin(tmp->value, value);
				else
					tmp->value = value;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		add_to_env_and_to_export(name, value);
	}
	free(name);
	free(value);
}

int	add_value_in_lists(char *cmd, int i, char *name, t_node *full_cmd)
{
	int		plus;
	char	*value;

	value = NULL;
	plus = 0;
	value = NULL;
	if (cmd[i] == ' ' || cmd[i] == '\0')
		i = add_to_export(cmd, i, full_cmd, name);
	else
	{
		if (cmd[i] == '+')
		{
			i++;
			plus = 1;
			if (cmd[i] != '=')
			{
				ft_putstr_fd("not a valid identifier", full_cmd->outf_fd);
				ft_putstr_fd("\n", full_cmd->outf_fd);
				return (0);
			}
		}
		i = get_value_too(cmd, i, &value);
		add_to_env_exp(name, value, plus);
	}
	return (i);
}

void	ft_export(t_node *full_cmd)
{
	char	*name;
	char	*cmd;
	int		i;

	name = NULL;
	i = 0;
	cmd = &(full_cmd->cmd[6]);
	if (!cmd[0])
		display_export(full_cmd);
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
			i = skip_of(cmd, i);
		else if (cmd[i] == ' ')
			while (cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
				i++;
		else
		{
			name = get_namee(cmd, &i, full_cmd);
			i = add_value_in_lists(cmd, i, name, full_cmd);
			name = NULL;
		}
	}
	g_gb.exit_code = 0;
}
