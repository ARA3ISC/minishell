/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:52:40 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:06:58 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	existe_spaces(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

void	fill_my_env(char **env)
{
	int		k;
	int		i;
	char	*name;

	k = 0;
	name = NULL;
	while (env[k])
	{
		i = 0;
		while (env[k][i] && env[k][i] != '=')
		{
			name = ft_strjoin_char(name, env[k][i]);
			i++;
		}
		ft_lstadd_back_env(&g_gb.my_env, ft_lstnew_env(name, getenv(name), 1,
				existe_spaces(getenv(name))));
		ft_lstadd_back_env(&g_gb.my_export, ft_lstnew_env(name, getenv(name), 1,
				existe_spaces(getenv(name))));
		name = NULL;
		k++;
	}
}

void	look_for_var(t_node *tmp, int j)
{
	char	*var;

	tmp->new_cmd = malloc(ft_strlen(getenv(tmp->exp_var[j])));
	var = getenv(tmp->exp_var[j]);
	if (var)
		printf("var : %s\n", var);
	else
		printf("Not exist\n");
}

char	*expanded_file_name(t_node *cmd, int i)
{
	char	*r;

	if (cmd->cmd_dt->file[i][1] && cmd->cmd_dt->file[i][0] == '$'
		&& cmd->cmd_dt->coted[i][0] != '2' && (cmd->cmd_dt->file[i][1] == '?'
			|| ft_isalnum(cmd->cmd_dt->file[i][1])))
	{
		if (cmd->cmd_dt->file[i][1] == '?')
			r = ft_strdup(ft_itoa(g_gb.exit_code));
		else
			r = get_from_my_env(&cmd->cmd_dt->file[i][1],
					cmd->cmd_dt->coted[i]);
		return (r);
	}
	return (NULL);
}

int	overridee(t_node *list_cmd, char *file, int i)
{
	int	fd;

	fd = 0;
	file = expanded_file_name(list_cmd, i);
	if (file && file[0] == '\0')
		return (0);
	if (file)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else
		fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (list_cmd->cmd_dt->to_open[i][0] == '1')
		list_cmd->outf_fd = fd;
	return (fd);
}
