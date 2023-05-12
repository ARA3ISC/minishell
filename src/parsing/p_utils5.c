/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:24:13 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 15:53:30 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alloc_variables(t_node *tmp)
{
	tmp->var_count = var_count(tmp->cmd);
	tmp->exp_var = malloc((tmp->var_count + 1) * sizeof(char *));
	if (!tmp->exp_var)
		return ;
}

char	*get_var(char *str, t_node *tmp, int j)
{
	int		len;
	int		i;
	char	*exp;

	(void)tmp;
	(void)j;
	len = 0;
	if (ft_isalnum(str[len]))
		while (ft_isalnum(str[len]) && str[len])
			len++;
	else if (str[len] == '?')
		len++;
	exp = malloc(len + 1);
	if (!exp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		exp[i] = str[i];
		i++;
	}
	exp[i] = '\0';
	return (exp);
}

void	skip3(t_node *tmp, int *i, int *j)
{
	if (tmp->cmd[*i] == 39)
	{
		(*i)++;
		help_check_quote(tmp->cmd, i, 39);
	}
	if (tmp->cmd[*i] == 34)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
		{
			if (tmp->cmd[*i + 1] && tmp->cmd[*i] == '$'
				&& (tmp->cmd[*i + 1] == '?' || ft_isalnum(tmp->cmd[*i + 1])))
			{
				tmp->exp_var[*j] = get_var(&tmp->cmd[*i + 1], tmp, *j);
				(*j)++;
			}
			(*i)++;
		}
		if (tmp->cmd[*i])
			(*i)++;
	}
}

void	look_for_dollar(t_node *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc_variables(tmp);
	while (tmp->cmd[i])
	{
		skip3(tmp, &i, &j);
		if (tmp->cmd[i] && tmp->cmd[i] == '$' && tmp->cmd[i + 1]
			&& (tmp->cmd[i + 1] == '?' || ft_isalnum(tmp->cmd[i + 1])))
		{
			tmp->exp_var[j] = get_var(&tmp->cmd[i + 1], tmp, j);
			j++;
		}
		if (tmp->cmd[i])
			i++;
	}
	tmp->exp_var[j] = NULL;
}

void	check_expanding(t_node *list_cmd)
{
	while (list_cmd)
	{
		look_for_dollar(list_cmd);
		list_cmd = list_cmd->next;
	}
}
