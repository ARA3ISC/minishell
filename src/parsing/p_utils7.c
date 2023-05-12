/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:44:11 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 16:02:56 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_reading(t_node *list_cmd, char *eof, char *coted)
{
	int		fds[2];
	char	*input;
	int		id;

	input = NULL;
	pipe(fds);
	id = fork();
	if (id == 0)
	{
		close(fds[0]);
		signal(SIGINT, exit_herdoc);
		read_from_herdoc(eof, input, fds[1], coted);
	}
	close(fds[1]);
	list_cmd->inf_fd = fds[0];
	wait(&g_gb.exit_code);
	g_gb.exit_code = WEXITSTATUS(g_gb.exit_code);
}

void	check_herdocs(t_node *list_cmd)
{
	char	*eof;
	int		i;
	int		j;

	while (list_cmd)
	{
		i = 0;
		j = 0;
		while (list_cmd->cmd[i])
		{
			if (list_cmd->cmd[i + 1] && list_cmd->cmd[i] == '<'
				&& list_cmd->cmd[i + 1] == '<')
			{
				eof = list_cmd->cmd_dt->eofs[j];
				start_reading(list_cmd, eof, list_cmd->cmd_dt->coted[j++]);
				if (g_gb.exit_code > 0)
					break ;
			}
			i++;
		}
		list_cmd = list_cmd->next;
	}
}

int	get_result(char *input, char *result, char *var, int i)
{
	if (input[i + 1] == '?')
	{
		result = ft_strdup(ft_itoa(g_gb.exit_code));
		i = i + 2;
	}
	else
	{
		result = get_from_my_env(var, "5");
		i = i + ft_strlen(var) + 1;
	}
	return (i);
}

char	*get_new_cmd(char *input, char **var, char *result, char *new_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] && input[i + 1] && input[i] == '$' && (input[i + 1] == '?'
				|| ft_isalnum(input[i + 1])))
		{
			i = get_result(input, result, var[j], i);
			if (result)
				new_cmd = ft_strjoin2(new_cmd, result);
			else
				new_cmd = ft_strjoin2(new_cmd, "\n");
			j++;
			continue ;
		}
		else if (input[i])
			new_cmd = ft_strjoin_char(new_cmd, input[i++]);
	}
	return (new_cmd);
}

char	*expend_herdocc(char *input)
{
	int		i;
	char	*result;
	char	**var;
	char	*new_cmd;
	int		j;

	new_cmd = NULL;
	result = NULL;
	if (input == NULL)
		return (NULL);
	var = malloc(sizeof(char *) * (get_len_vars(input) + 1));
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] && (input[i + 1] == '?'
				|| ft_isalnum(input[i + 1])))
			var[j++] = get_var(&input[i + 1], NULL, 0);
		i++;
	}
	var[j] = NULL;
	new_cmd = get_new_cmd(input, var, result, new_cmd);
	free_2d_table(var);
	return (new_cmd);
}
