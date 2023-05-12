/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:17:18 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 20:06:58 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skipiiin(char *cmd_tmp, int i)
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

char	*get_print_help(char *cmd_tmp, int *i, char *print, int *nl)
{
	int	k;

	k = *i;
	*i = *i + 2;
	while (cmd_tmp[*i] && cmd_tmp[*i] == 'n')
		(*i)++;
	if (cmd_tmp[*i] && cmd_tmp[*i] != ' ')
	{
		print = ft_strjoin_char(print, cmd_tmp[k]);
		*i = k + 1;
	}
	else
		*nl = 0;
	while (cmd_tmp[*i] && cmd_tmp[*i] == ' ')
		(*i)++;
	return (print);
}

char	*get_print_from_quots(char *cmd_tmp, int *i, int nbr, char *print)
{
	(*i)++;
	while (cmd_tmp[*i] && cmd_tmp[*i] != nbr)
	{
		print = ft_strjoin_char(print, cmd_tmp[*i]);
		(*i)++;
	}
	if (cmd_tmp[*i])
		(*i)++;
	return (print);
}

char	*get_print(char *cmd_tmp, int *i, char **print, int *nl)
{
	while (cmd_tmp[*i])
	{
		if (cmd_tmp[*i] == 34)
			*print = get_print_from_quots(cmd_tmp, i, 34, *print);
		else if (cmd_tmp[*i] == 39)
			*print = get_print_from_quots(cmd_tmp, i, 39, *print);
		else if (cmd_tmp[*i] == '-' && cmd_tmp[*i + 1] == 'n' && (cmd_tmp[*i
					+ 2] == 'n' || cmd_tmp[*i + 2] == ' ' || cmd_tmp[*i
					+ 2] == '\0'))
			*print = get_print_help(cmd_tmp, i, *print, nl);
		else if (cmd_tmp[*i] == '<' || cmd_tmp[*i] == '>')
			*i = skipiiin(cmd_tmp, *i);
		else
			while (cmd_tmp[*i] && cmd_tmp[*i] != 39 && cmd_tmp[*i] != 34
				&& cmd_tmp[*i] != '<' && cmd_tmp[*i] != '>')
				*print = ft_strjoin_char(*print, cmd_tmp[(*i)++]);
	}
	return (*print);
}



void	ft_echo(t_node *cmd)
{
	char	*cmd_tmp;
	int		i;
	char	*print;
	int		nl;

	print = NULL;
	nl = 1;
	cmd_tmp = &(cmd->new_cmd[4]);
	if (cmd_tmp[0] == ' ' || cmd_tmp[0] == '<' || cmd_tmp[0] == '>')
	{
		i = 0;
		while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
			i++;
		print = get_print(cmd_tmp, &i, &print, &nl);
	}
	if (print)
	{
		print = ft_strtrim(print, " ");
		ft_putstr_fd(print, cmd->outf_fd);
		if (nl)
			ft_putstr_fd("\n", cmd->outf_fd);
	}
	else
		ft_putstr_fd("\n", cmd->outf_fd);
	free(print);
	g_gb.exit_code = 0;
}
