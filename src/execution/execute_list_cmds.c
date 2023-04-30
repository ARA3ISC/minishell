/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:05:47 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/30 16:15:35 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(void)
{
	// printf("path[0] :%c | path[3] :%c\n", env->name[0], env->name[3]);


	char **paths;
	// char **split_path;
	// int i = 0;
	while (g_gb.my_env)
	{
		if (g_gb.my_env->name[0] == 'P' && g_gb.my_env->name[3] == 'H')
		{
			// paths = ft_strchr(g_gb.my_env[i] ,'/');
			paths = ft_split(g_gb.my_env->value, ':');
			return paths;
		}
		g_gb.my_env = g_gb.my_env->next;
	}
	return NULL;
}

char **check_flags(char *cmd)
{
	char **new_cmd;

	new_cmd = ft_split(cmd, 32);
	return new_cmd;
}

void	cmd_not_found(char *cmd)
{
	printf("%s: command not found\n", cmd);
	g_gb.exit_code = 127;
	exit(127);
}

void	check_cmds(t_node *list_cmd)
{
	char **paths;
	char *f_cmd;
	int i = 0;

	paths = get_paths();
	// printf("path[0]\n");
	// cmd_flags = check_flags(cmd);

	if (access(list_cmd->cmd_flags[0], X_OK) == 0)
	{
		execve(list_cmd->cmd_flags[0], list_cmd->cmd_flags, NULL);
	}
	else
	{
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(paths[i], list_cmd->cmd_flags[0]);
			if (access(f_cmd, X_OK) == 0)
			{
				execve(f_cmd, list_cmd->cmd_flags, NULL);
				// printf("hhh\n");
			}
			i++;
		}
	}
	// printf("command not found\n");
	cmd_not_found(list_cmd->cmd_flags[0]);
}

void	initialize_fds(t_node *list_cmd, int *fds)
{

	if(!list_cmd->index)
	{
		if(list_cmd->outf_fd == 1)
			list_cmd->outf_fd = fds[1];
		g_gb.save_fd = fds[0];
	}
	else if(list_cmd->index == g_gb.infos->cmd_count - 1)
	{
		list_cmd->inf_fd = g_gb.save_fd;
	}
	else
	{
		if(list_cmd->outf_fd == 1)
			list_cmd->outf_fd = fds[1];
		list_cmd->outf_fd = g_gb.save_fd;
		g_gb.save_fd = fds[0];

	}
}

void execute_list_of_cmds(t_node *list_cmd)
{
	int p;
	int fk;
	int fds[2];

	while(list_cmd)
	{

		if (ft_lstsize(list_cmd) > 1)
		{
			if(list_cmd->index != g_gb.infos->cmd_count - 1)
			{
				p = pipe(fds);
				if(p == -1)
					perror("error open pipe");
				initialize_fds(list_cmd, fds);
				fk = fork();
				if(fk == 0)
				{
					close(fds[0]);
					dup2(g_gb.save_fd, 0);
					dup2(list_cmd->outf_fd, 1);
					printf("ldkhl\n");
					check_cmds(list_cmd);

				}
				wait(NULL);

			}

			// printf("***\n");
			// if (list_cmd->next != NULL)
			// 	close(list_cmd->inf_fd);
			// if (dup2(list_cmd->outf_fd, 1) == -1)
			// 	perror("error dup");
			// if (list_cmd->next == NULL)
			// {
			// 	if (dup2(1, list_cmd->outf_fd) == -1)
			// 		perror("error dup");
			// }

		}
		else
		{
			fk = fork();
			if(fk == 0)
			{
				dup2(list_cmd->outf_fd, 1);
				dup2(list_cmd->inf_fd, 0);
				printf("ldkhl\n");
				check_cmds(list_cmd);

			}
		}
		// printf("%d\t%d\t%d", list_cmd->outf_fd, list_cmd->outf_fd, list_cmd->inf_fd);
		// dup2(list_cmd->outf_fd, 1);

		// close(list_cmd->outf_fd);
		// close(list_cmd->inf_fd);
		// dup2(list_cmd->inf_fd, 0);
		// while (wait(NULL) != -1);
		wait(NULL);
		printf("hello\n");
		list_cmd = list_cmd->next;
	}
}
