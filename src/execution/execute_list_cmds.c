/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:05:47 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/30 22:49:36 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(void)
{
	char	**paths;

	// printf("path[0] :%c | path[3] :%c\n", env->name[0], env->name[3]);
	// char **split_path;
	// int i = 0;
	while (g_gb.my_env)
	{
		if (g_gb.my_env->name[0] == 'P' && g_gb.my_env->name[3] == 'H')
		{
			// paths = ft_strchr(g_gb.my_env[i] ,'/');
			paths = ft_split(g_gb.my_env->value, ':');
			return (paths);
		}
		g_gb.my_env = g_gb.my_env->next;
	}
	return (NULL);
}

char	**check_flags(char *cmd)
{
	char	**new_cmd;

	new_cmd = ft_split(cmd, 32);
	return (new_cmd);
}

void	cmd_not_found(char *cmd)
{
	printf("%s: command not found\n", cmd);
	g_gb.exit_code = 127;
	exit(127);
}

void	check_cmds(t_node *list_cmd)
{
	char	**paths;
	char	*f_cmd;
	int		i;

	i = 0;
	paths = get_paths();
	// printf("path[0]\n");
	// cmd_flags = check_flags(cmd);
	if (access(list_cmd->cmd_flags[0], X_OK) == 0)
		execve(list_cmd->cmd_flags[0], list_cmd->cmd_flags, NULL);
	else
	{
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(paths[i], list_cmd->cmd_flags[0]);
			if (access(f_cmd, X_OK) == 0)
				execve(f_cmd, list_cmd->cmd_flags, NULL);
			i++;
		}
	}
	cmd_not_found(list_cmd->cmd_flags[0]);
}

// void	initialize_fds(t_node **list_cmd, int *fds)
// {

// 	if(!(*list_cmd)->index)
// 	{
// 		// if((*list_cmd)->outf_fd == 1)
// 		// 	(*list_cmd)->outf_fd = fds[1];
// 		g_gb.save_fd = fds[0];
// 	}
// 	else if((*list_cmd)->index == g_gb.infos->cmd_count - 1)
// 	{
// 		(*list_cmd)->inf_fd = g_gb.save_fd;
// 	}
// 	else
// 	{
// 		if((*list_cmd)->outf_fd == 1)
// 			(*list_cmd)->outf_fd = fds[1];
// 		(*list_cmd)->outf_fd = g_gb.save_fd;
// 		g_gb.save_fd = fds[0];

// 	}
// }

void	ft_putstrfd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}



void close_fds(t_node *node, t_node *tmp)
{
	// printf("tmp : %s\nnode : %s\n", tmp->cmd, node->cmd);
	while(tmp && tmp->index < node->index)
	{
		if(tmp->index + 1 == node->index)
		{
			close(tmp->fds[1]);
			dup2(tmp->fds[0], 0);
		}
		else
		{
			close(tmp->fds[0]);
			close(tmp->fds[1]);
		}
		tmp = tmp->next;
	}
}


void	execute_list_of_cmds(t_node *list_cmd)
{
	int	fk;
	int	len;
	t_node *tmp;

	tmp = list_cmd;

	len = ft_lstsize(list_cmd);
	while (list_cmd)
	{
		if (len > 1)
		{
			if (list_cmd->index != g_gb.infos->cmd_count - 1)
			{
				if (pipe(list_cmd->fds) == -1)
					perror("error open pipe");
				fk = fork();
				if (fk == 0)
				{
					close(list_cmd->fds[0]);
					dup2(list_cmd->fds[1], 1);
					close_fds(list_cmd, tmp);
					check_cmds(list_cmd);
				}
			}
			else
			{
				// fk = fork();
				// if (fk == 0)
				// {
					close_fds(list_cmd, tmp);
					// printf("ana hna\n");
					check_cmds(list_cmd);
					
				// }
				while (wait(NULL) != -1)
						;
				
			}
		}
		else
		{
			fk = fork();
			if (fk == 0)
			{
				dup2(list_cmd->outf_fd, 1);
				dup2(list_cmd->inf_fd, 0);
				check_cmds(list_cmd);
			}
			while (wait(NULL) != -1)
					;
		}
		
		list_cmd = list_cmd->next;
	}
}
