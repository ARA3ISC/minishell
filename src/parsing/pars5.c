/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:31:44 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:06:02 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detail_cmd(t_node *list_cmd)
{
	while (list_cmd)
	{
		list_cmd->cmd_dt = malloc(sizeof(t_cmd));
		list_cmd->cmd_dt->op = malloc(sizeof(char *) * (list_cmd->op_count
					+ 1));
		list_cmd->cmd_dt->file = malloc(sizeof(char *) * (list_cmd->op_count
					+ 1));
		list_cmd->cmd_dt->coted = malloc(sizeof(char *) * (list_cmd->op_count
					+ 1));
		list_cmd->cmd_dt->to_open = malloc(sizeof(char *) * (list_cmd->op_count
					+ 1));
		list_cmd->cmd_dt->eofs = malloc(sizeof(char *)
				* (list_cmd->herdocs_count + 1));
		get_details(list_cmd);
		if (g_gb.exit_code == 404)
			return (0);
		list_cmd = list_cmd->next;
	}
	return (1);
}

char	*get_eof(char *after_herd)
{
	int		i;
	int		c;
	int		len;
	char	*eof;

	i = 0;
	c = 0;
	len = 0;
	while (after_herd[i] == 32 || after_herd[i] == '\t')
		i++;
	if (after_herd[i] == 34)
	{
		i++;
		c = i;
		while (after_herd[i++] != 34)
			len++;
	}
	while (after_herd[i] && after_herd[i] != 32 && after_herd[i++] != 34)
		len++;
	eof = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i <= len && after_herd[c] != 34)
		eof[i++] = after_herd[c++];
	eof[i] = '\0';
	return (eof);
}

void	exit_herdoc(int signo)
{
	if (signo == SIGINT)
		exit(1);
}

int	ft_twodim_len(char **p)
{
	int	i;

	i = 0;
	if (!p || !p[i])
		return (0);
	while (p[i])
		i++;
	return (i);
}

char	*search_and_replace(char *str, char a, char b)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == a)
			str[i] = b;
		i++;
	}
	return (str);
}
