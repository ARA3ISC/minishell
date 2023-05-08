/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:21:55 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 00:15:17 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int join_it(t_node *list_cmd, int i, int p, char **new_cmd)
{
    i++;
    while (list_cmd->cmd[i] && list_cmd->cmd[i] != p)
    {
        (*new_cmd) = ft_strjoin_char((*new_cmd), list_cmd->cmd[i]);
        i++;
    }
    i++;
    return i;
}

int skip_op(t_node *list_cmd, char **new_cmd, int i)
{
    (*new_cmd) = ft_strjoin_char((*new_cmd), '&');
    i++;
    if (list_cmd->cmd[i] && (list_cmd->cmd[i] == '>'
            || list_cmd->cmd[i] == '<'))
        i++;
    while (list_cmd->cmd[i] && list_cmd->cmd[i] == 32)
        i++;
    while (list_cmd->cmd[i] && list_cmd->cmd[i] != 32)
        i++;

    return i;
}



int    get_correct_flags(t_node *list_cmd, int is_quoted, char **new_cmd, int i)
{
	while (list_cmd->cmd[i])
	{
		if (list_cmd->cmd[i] == 34)
		{
			is_quoted = 1;
			i = join_it(list_cmd, i, 34, new_cmd);
		}
		else if (list_cmd->cmd[i] == 39)
		{
			is_quoted = 1;
            i = join_it(list_cmd, i, 39, new_cmd);
		}
		else if (list_cmd->cmd[i] && (list_cmd->cmd[i] == '>'
					|| list_cmd->cmd[i] == '<'))
			i = skip_op(list_cmd, new_cmd, i);
		else if (list_cmd->cmd[i] == 32)
		{
			while (list_cmd->cmd[i] && list_cmd->cmd[i] == 32)
				i++;
			(*new_cmd) = ft_strjoin_char((*new_cmd), '&');
		}
		else
			(*new_cmd) = ft_strjoin_char((*new_cmd), list_cmd->cmd[i++]);
	}
    return is_quoted;
}

void	cmd_flags_1st_case(t_node *list_cmd)
{
	char	*new_cmd;
	char	*expanded_cmd;
	char	*cmd_tosplit;
	int		is_quoted;
	int		i;

	new_cmd = NULL;
	is_quoted = 0;
    i = 0;
	is_quoted = get_correct_flags(list_cmd, is_quoted, &new_cmd, i);
	expanded_cmd = expend_herdocc(new_cmd);
	if (!is_quoted)
	{
		cmd_tosplit = search_and_replace(expanded_cmd, ' ', '&');
		list_cmd->cmd_flags = ft_split(cmd_tosplit, '&');
	}
	else
		list_cmd->cmd_flags = ft_split(expanded_cmd, '&');
	free(new_cmd);
	free(expanded_cmd);
	if (!ft_twodim_len(list_cmd->cmd_flags))
		list_cmd->only_heredoc = true;
}

void	get_cmd_with_flags(t_node *list_cmd)
{
	while (list_cmd)
	{
		cmd_flags_1st_case(list_cmd);
		list_cmd = list_cmd->next;
	}
}
