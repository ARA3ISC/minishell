/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 21:14:19 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	count_herdocs(char *full_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (full_cmd[i])
	{
		if (full_cmd[i + 1] && full_cmd[i] == '<' && full_cmd[i + 1] == '<')
			count++;
		i++;
	}
	if (count > 16)
		exit(print_error("maximum here-document count exceeded", 2));
}

void	print_list(t_node *list_cmd)
{
	int	i;

	while (list_cmd)
	{
		i = 0;
		while (list_cmd->cmd_dt->file[i])
			i++;
		list_cmd = list_cmd->next;
	}
}

void	fill_my_array_env(char **env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	g_gb.env_array = malloc(sizeof(char *) * (len + 1));
	while (env[i])
	{
		g_gb.env_array[i] = ft_strdup(env[i]);
		i++;
	}
	g_gb.env_array[i] = NULL;
}

void	begin_manipulation(char *full_cmd, t_node **list_cmd)
{
	g_gb.error = fill_struct(full_cmd, list_cmd);
	if (g_gb.error != 0)
	{
		get_number_of_tokens(full_cmd, *list_cmd);
		g_gb.error = detail_cmd(*list_cmd);
		if (g_gb.error != 0)
		{
			check_expanding(*list_cmd);
			expanding(*list_cmd);
			check_herdocs(*list_cmd);
			get_cmd_with_flags(*list_cmd);
			execution(*list_cmd);
		}
		free(g_gb.infos);
		ft_lstclear(list_cmd);
	}
}

void	parsing(char **env, t_node *list_cmd)
{
	char	*full_cmd;

	banner();
	signal(SIGINT, SIG_IGN);
	fill_my_env(env);
	fill_my_array_env(env);
	signal(SIGINT, signal_c_received);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		full_cmd = readline(MINISHELL);
		if (!full_cmd)
			break ;
		add_history(full_cmd);
		g_gb.error = all_error(full_cmd);
		if (!g_gb.error)
			begin_manipulation(full_cmd, &list_cmd);
		free(full_cmd);
		list_cmd = NULL;
		g_gb.error = 0;
	}
	printf("exit\n");
	exit(g_gb.exit_code);
}
