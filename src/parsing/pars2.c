/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:07:41 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:04:54 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_check_quote(char *string, int *i, int qt)
{
	int	check;

	check = 1;
	while (string[*i])
	{
		if (string[*i] == qt)
		{
			check = 0;
			break ;
		}
		(*i)++;
	}
	return (check);
}

int	checking_quotes(char c, int *i, char *cmd)
{
	int	check;
	int	qt;

	check = 0;
	if (c == 39)
	{
		(*i)++;
		qt = 39;
		check = help_check_quote(cmd, i, qt);
	}
	if (c == 34)
	{
		(*i)++;
		qt = 34;
		check = help_check_quote(cmd, i, qt);
	}
	return (check);
}

int	checking_redirection_in_the_last(char *cmd)
{
	int	i;

	if (cmd != NULL)
	{
		i = ft_strlen(cmd);
		if (i != 0)
			i--;
		while (i > 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
			i--;
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			print_error("Syntax error", 258);
			return (1);
		}
	}
	return (0);
}

void	skip_p(t_node *tmp, int *i, int *len)
{
	if (tmp->cmd[*i] == 34)
	{
		(*len)++;
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
		{
			(*i)++;
			(*len)++;
		}
	}
	if (tmp->cmd[*i] == 39)
	{
		(*len)++;
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
		{
			(*i)++;
			(*len)++;
		}
	}
}

int	get_len_to_alloc(t_node *tmp, int *i, int len)
{
	while (tmp->cmd[*i] && tmp->cmd[*i] != 32 && tmp->cmd[*i] != '\t'
		&& tmp->cmd[*i] != '<' && tmp->cmd[*i] != '>')
	{
		skip_p(tmp, i, &len);
		len++;
		(*i)++;
	}
	return (len);
}
