/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:07:37 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:05:14 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_for_op_and_file(t_node *tmp, int i, int j)
{
	int	len;

	len = 0;
	if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
	{
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 3);
		i++;
	}
	else
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 2);
	while (tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	len = get_len_to_alloc(tmp, &i, len);
	tmp->cmd_dt->file[j] = malloc(sizeof(char) * len + 1);
	if (!tmp->cmd_dt->file[j])
		exit(1);
	return (len);
}

void	skippo(char *cmd_dt_file_d, int *i, char **n_name, int *j)
{
	if (cmd_dt_file_d[*i] == 34)
	{
		(*i)++;
		while (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] != 34)
		{
			(*n_name)[(*j)++] = cmd_dt_file_d[*i];
			(*i)++;
		}
		(*i)++;
	}
	if (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] == 39)
	{
		(*i)++;
		while (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] != 39)
		{
			(*n_name)[(*j)++] = cmd_dt_file_d[*i];
			(*i)++;
		}
		(*i)++;
	}
}

char	*get_n_name(char *cmd_dt_file_d, int j, char **n_name)
{
	int	i;

	i = 0;
	while (cmd_dt_file_d[i])
	{
		skippo(cmd_dt_file_d, &i, n_name, &j);
		if (cmd_dt_file_d[i] && cmd_dt_file_d[i] != 34
			&& cmd_dt_file_d[i] != 39)
		{
			(*n_name)[j++] = cmd_dt_file_d[i];
			i++;
		}
	}
	(*n_name)[j] = '\0';
	return (*n_name);
}

char	*working_in_the_name_of_the_file(t_node *cmd, int len, int d)
{
	int		i;
	int		j;
	char	*n_name;

	i = 0;
	j = 0;
	while (cmd->cmd_dt->file[d][i])
	{
		if (cmd->cmd_dt->file[d][i] == '\"')
			cmd->cmd_dt->coted[d][0] = '1';
		else if (cmd->cmd_dt->file[d][i] == '\'')
			cmd->cmd_dt->coted[d][0] = '2';
		i++;
	}
	i = 0;
	n_name = malloc(len + 1);
	n_name = get_n_name(cmd->cmd_dt->file[d], j, &n_name);
	free(cmd->cmd_dt->file[d]);
	return (n_name);
}

void	help_fill_file_name(t_node *tmp, int d, int *k, int *i)
{
	if (tmp->cmd[*i] == 34)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
			tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		printf("kk > |%d|\n", *k);
	}
	else if (tmp->cmd[*i] && tmp->cmd[*i] == 39)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
			tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
	}
	else
		(*i)++;
}
