/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:25:53 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/07 15:30:19 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_oaf(char *cmd_tmp, int i)
{
	i++;
	if (cmd_tmp[i] == '>')
		i++;
	while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
		i++;
	while (cmd_tmp[i] && cmd_tmp[i] != 32 && cmd_tmp[i] != '\t')
		i++;
	while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
		i++;
	return (i);
}

char	*get_path(char *cmd_tmp, int *i)
{
	char	*path;

	path = NULL;
	while (cmd_tmp[*i])
	{
		if (cmd_tmp[*i] == 34)
		{
			(*i)++;
			while (cmd_tmp[*i] && cmd_tmp[*i] != 34)
				path = ft_strjoin_char(path, cmd_tmp[(*i)++]);
			(*i)++;
		}
		else if (cmd_tmp[*i] == 39)
		{
			(*i)++;
			while (cmd_tmp[*i] && cmd_tmp[*i] != 39)
				path = ft_strjoin_char(path, cmd_tmp[(*i)++]);
			(*i)++;
		}
		else if (cmd_tmp[*i] == '<' || cmd_tmp[*i] == '>')
			*i = skip_oaf(cmd_tmp, *i);
		else
			path = ft_strjoin_char(path, cmd_tmp[(*i)++]);
	}
	return (path);
}

void	ft_cd(t_node *full_cmd)
{
	char	*path;
	char	*cmd_tmp;
	int		i;

	path = NULL;
	cmd_tmp = &(full_cmd->new_cmd[2]);
	if (cmd_tmp[0] == ' ')
	{
		i = 0;
		while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
			i++;
		path = get_path(cmd_tmp, &i);
	}
	if (chdir(path) == -1)
		perror("error change directory");
	g_gb.exit_code = 0;
	free(path);
}
