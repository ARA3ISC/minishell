/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:26:33 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 03:37:09 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int skip_a(char *cmd_tmp, int i)
{
	i++;
	if (cmd_tmp[i] && (cmd_tmp[i] == '<' || cmd_tmp[i] == '>'))
		i++;
	while (cmd_tmp[i] && cmd_tmp[i] == 32)
		i++;
	while (cmd_tmp[i] && cmd_tmp[i] != 32)
		i++;
	return (i);
}


int help_flags(char *cmd_tmp, char **flags, int i)
{
	if (cmd_tmp[i] && cmd_tmp[i] == 32)
	{
		*flags = ft_strjoin_char(*flags, '&');
		while (cmd_tmp[i] && cmd_tmp[i] == 32)
			i++;
	}
	return i;
}

int get_flags(char *cmd_tmp, int i, char **flags)
{
	while (cmd_tmp[i])
	{
		i = help_flags(cmd_tmp, flags, i);
		
		if (cmd_tmp[i] && (cmd_tmp[i] == '<' || cmd_tmp[i] == '>'))
			i = skip_a(cmd_tmp, i);
		else if (cmd_tmp[i] && cmd_tmp[i] == 34)
		{
			i++;
			while (cmd_tmp[i] && cmd_tmp[i] != 34)
				*flags = ft_strjoin_char(*flags, cmd_tmp[i++]);
			if(cmd_tmp[i])
				i++;
		}
		else if (cmd_tmp[i] && cmd_tmp[i] == 39)
		{
			i++;
			while (cmd_tmp[i] && cmd_tmp[i] != 39)
				*flags = ft_strjoin_char(*flags, cmd_tmp[i]);
			if(cmd_tmp[i])
				i++;
		}
		else
			*flags = ft_strjoin_char(*flags, cmd_tmp[i++]);
	}
	return i;
}

void finish(char **split_flags, t_node *full_cmd, int i)
{
	if (split_flags && ft_is_nbr(split_flags[0]) && i > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", full_cmd->outf_fd);
		ft_putstr_fd("\n", full_cmd->outf_fd);
	}
	else if (split_flags && ft_is_nbr(split_flags[0]) && i == 1)
	{

		exit(ft_atoi(split_flags[0]));
	}
	else
	{
		exit(g_gb.exit_code);
	}
}

void	ft_exit(t_node *full_cmd)
{
	char	*cmd_tmp;
	int		i;
	char	*flags;
	char	**split_flags;

	i = 0;
	flags = NULL;
	cmd_tmp = &(full_cmd->new_cmd[4]);
	while (cmd_tmp[i] && cmd_tmp[i] == 32)
		i++;
	i = get_flags(cmd_tmp, i, &flags);

	split_flags = ft_split(flags, '&');
	i = 0;
	while (split_flags && split_flags[i])
		i++;
	if (split_flags && !ft_is_nbr(split_flags[0]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required",
				full_cmd->outf_fd);
		ft_putstr_fd("\n", full_cmd->outf_fd);
		exit(255);
	}
	finish(split_flags, full_cmd, i);
	free(flags);
	free_2d_table(split_flags);

}
