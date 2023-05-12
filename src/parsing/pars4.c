/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:07:24 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:05:40 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_file_name(t_node *tmp, int i, int j)
{
	int	k;

	k = 0;
	while (tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while (tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t'
		&& tmp->cmd[i] != '<' && tmp->cmd[i] != '>')
	{
		tmp->cmd_dt->file[j][k++] = tmp->cmd[i];
		if (tmp->cmd_dt->file[j][0] == '#')
		{
			print_error("syntax error", 404);
			return (1);
		}
		help_fill_file_name(tmp, j, &k, &i);
	}
	tmp->cmd_dt->file[j][k] = '\0';
	return (0);
}

void	fill_opp(t_node *tmp, int *i, int j)
{
	tmp->cmd_dt->op[j][0] = tmp->cmd[*i];
	(*i)++;
	if (tmp->cmd[*i] && (tmp->cmd[*i] == '<' || tmp->cmd[*i] == '>'))
	{
		if (tmp->cmd[*i] == '<')
			tmp->cmd_dt->op[j][1] = '<';
		else
			tmp->cmd_dt->op[j][1] = '>';
		tmp->cmd_dt->op[j][2] = '\0';
		(*i)++;
	}
	else
		tmp->cmd_dt->op[j][1] = '\0';
	tmp->cmd_dt->to_open[j] = ft_strdup("1");
}

void	fill_file(t_node *tmp, int *i, int *k, int j)
{
	int	is_eof;
	int	len;

	is_eof = 0;
	if (tmp->cmd[*i + 1] && tmp->cmd[*i] == '<' && tmp->cmd[*i + 1] == '<')
		is_eof = 1;
	len = allocate_for_op_and_file(tmp, *i + 1, j);
	if (tmp->cmd[*i] && tmp->cmd[*i] == '<' && tmp->cmd[*i + 1] == '>')
	{
		tmp->cmd_dt->op[j][0] = '>';
		tmp->cmd_dt->op[j][1] = '\0';
		tmp->cmd_dt->to_open[j] = ft_strdup("0");
		*i = *i + 2;
	}
	else
	{
		fill_opp(tmp, i, j);
	}
	g_gb.error = fill_file_name(tmp, *i, j);
	tmp->cmd_dt->coted[j] = ft_strdup("0");
	if (g_gb.error)
		return ;
	tmp->cmd_dt->file[j] = working_in_the_name_of_the_file(tmp, len, j);
	if (is_eof)
		tmp->cmd_dt->eofs[(*k)++] = ft_strdup(tmp->cmd_dt->file[j]);
}

void	skip_and_fill_fname(t_node *tmp, int *i, int *k, int *j)
{
	if (tmp->cmd[*i] == 34)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
			(*i)++;
		(*i)++;
	}
	else if (tmp->cmd[*i] == 39)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
			(*i)++;
		(*i)++;
	}
	else if (tmp->cmd[*i] == '>' || tmp->cmd[*i] == '<')
	{
		fill_file(tmp, i, k, *j);
		(*j)++;
	}
	else
		(*i)++;
}

void	get_details(t_node *tmp)
{
	int	i;
	int	j;
	int	k;
	int	is_eof;

	i = 0;
	j = 0;
	k = 0;
	while (tmp->cmd[i])
	{
		is_eof = 0;
		skip_and_fill_fname(tmp, &i, &k, &j);
	}
	tmp->cmd_dt->op[j] = NULL;
	tmp->cmd_dt->file[j] = NULL;
	tmp->cmd_dt->to_open[j] = NULL;
	tmp->cmd_dt->coted[j] = NULL;
	tmp->cmd_dt->eofs[k] = NULL;
}
