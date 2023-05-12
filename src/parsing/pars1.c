/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:07:46 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:04:38 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d_table(char **t)
{
	int	i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	skipping(char *cmd, int *i)
{
	if (cmd[*i] == 39)
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != 39)
			(*i)++;
		(*i)++;
	}
	else if (cmd[*i] && cmd[*i] == 34)
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != 34)
			(*i)++;
		(*i)++;
	}
	else
		(*i)++;
}

char	**spliting_by_pipe(char *cmd)
{
	int		i;
	char	**all_cmds;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '|')
			cmd[i] = '&';
		skipping(cmd, &i);
	}
	all_cmds = ft_split(cmd, '&');
	return (all_cmds);
}

int	error_stx(char **all_cmds)
{
	if (!all_cmds[0])
	{
		free(all_cmds);
		print_error(NULL, 0);
		return (0);
	}
	if (check_whitespaces(all_cmds) && all_cmds[1])
	{
		free(all_cmds);
		print_error("syntax error near unexpected token `|'", 258);
		return (0);
	}
	return (1);
}

int	fill_struct(char *cmd, t_node **list_cmd)
{
	int		i;
	char	**all_cmds;
	char	*cmd_tmp;

	i = 0;
	cmd_tmp = ft_strdup(cmd);
	all_cmds = spliting_by_pipe(cmd_tmp);
	free(cmd_tmp);
	if (!error_stx(all_cmds))
		return (0);
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		all_cmds[i] = ft_strtrim(all_cmds[i], "\t");
		ft_lstadd_back(list_cmd, ft_lstnew(all_cmds[i]));
		i++;
	}
	free(all_cmds);
	return (1);
}
