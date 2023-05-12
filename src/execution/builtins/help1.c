/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:27:34 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:34:55 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_name_from_simple_quot(char *cmd, char **name, int i, t_node *full_cmd)
{
	i++;
	while (cmd[i] && cmd[i] != 39)
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

char	*get_namee(char *cmd, int *i, t_node *full_cmd)
{
	char	*name;

	name = NULL;
	while (cmd[*i] && cmd[*i] != '+' && cmd[*i] != '=' && cmd[*i] != ' ')
	{
		if (cmd[*i] == 34)
			*i = get_name_from_double_quot(cmd, &name, *i, full_cmd);
		else if (cmd[*i] == 39)
			*i = get_name_from_simple_quot(cmd, &name, *i, full_cmd);
		else
		{
			if (!ft_isalnum(cmd[*i]))
			{
				ft_putstr_fd("minishell: export: not a valid identifier",
					full_cmd->outf_fd);
				ft_putstr_fd("\n", full_cmd->outf_fd);
				return (NULL);
			}
			name = ft_strjoin_char(name, cmd[(*i)++]);
		}
		display_export(full_cmd);
	}
	return (name);
}

int	ft_is_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
