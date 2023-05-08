/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:05:47 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 00:10:59 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(void)
{
	char	**paths;

	while (g_gb.my_env)
	{
		if (g_gb.my_env->name[0] == 'P' && g_gb.my_env->name[3] == 'H')
		{
			paths = ft_split(g_gb.my_env->value, ':');
			return (paths);
		}
		g_gb.my_env = g_gb.my_env->next;
	}
	return (NULL);
}

void	printf_error(char *msg, char *cmd)
{
	usleep(200);
	write(2, "minishell :", ft_strlen("minishell :"));
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, " :", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);	
}

void cmd_not_found(char *full_cmd)
{
	char *cmd = NULL;
	int i;

	i = 0;
	if (!full_cmd || !ft_strlen(full_cmd))
	{
		printf("minishell: : command not found\n");
		g_gb.exit_code = 127;
		exit(127);
	}
	while(full_cmd[i] && full_cmd[i] != ' ' && full_cmd[i] != '<' && full_cmd[i] != '>')
	{
		cmd = ft_strjoin_char(cmd, full_cmd[i]);
		i++;
	}
	printf_error("command not found", cmd);
	g_gb.exit_code = 127;
	exit(127);

}

void	check_cmds(t_node *list_cmd)
{
	char	**paths;
	char	*f_cmd;
	int		i;

	i = 0;
	if (list_cmd->cmd_flags && access(list_cmd->cmd_flags[0], X_OK) == 0)
		execve(list_cmd->cmd_flags[0], list_cmd->cmd_flags, g_gb.env_array);
	else if(list_cmd->cmd_flags)
	{
		paths = get_paths();
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(paths[i], list_cmd->cmd_flags[0]);
			if (access(f_cmd, X_OK) == 0)
				execve(f_cmd, list_cmd->cmd_flags, g_gb.env_array);
			i++;
		}
	}
	error_case(list_cmd);
}

void	execute_list_of_cmds(t_node *list_cmd)
{
	int	len;
	t_node *tmp;

	tmp = list_cmd;
	len = ft_lstsize(list_cmd);
	while (list_cmd)
	{
		g_gb.error = open_files(list_cmd);
		if (g_gb.error == 0)
		{
			if (list_cmd)
				list_cmd = list_cmd->next;
			continue; 
		}
		if(is_herdoc(list_cmd))
		{
			list_cmd = list_cmd->next;
			continue; 
		}
		execute_all_cmds(list_cmd, tmp, len);
		list_cmd = list_cmd->next;
	}
}
