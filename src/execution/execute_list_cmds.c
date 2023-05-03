/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:05:47 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/03 16:39:56 by eej-jama         ###   ########.fr       */
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


void cmd_not_found(char *full_cmd)
{
	char *cmd = NULL;
	int i;

	i = 0;
	while(full_cmd[i] && full_cmd[i] != ' ' && full_cmd[i] != '<' && full_cmd[i] != '>')
	{
		cmd = ft_strjoin_char(cmd, full_cmd[i]);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd);
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
		execve(list_cmd->cmd_flags[0], list_cmd->cmd_flags, g_gb.env_array);
	else
	{
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(paths[i], list_cmd->cmd_flags[0]);
			if (access(f_cmd, X_OK) == 0)
				execve(f_cmd, list_cmd->cmd_flags, g_gb.env_array);
			i++;
		}
	}
	// printf("flags : %s\n", list_cmd->cmd_flags[0]);
	if (list_cmd->cmd_flags[0])
		cmd_not_found(list_cmd->cmd_flags[0]);
	else
		exit(0);
}

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
	while(tmp && tmp->index < node->index)
	{
		if(tmp->index + 1 == node->index)
		{
			close(tmp->fds[1]);
			if(tmp->inf_fd == 0)
				dup2(tmp->fds[0], 0);
			else if (tmp->inf_fd > 2)
				dup2(tmp->inf_fd, 0);
		}
		else
		{
			close(tmp->fds[0]);
			close(tmp->fds[1]);
		}
		tmp = tmp->next;
	}
}

void close_all_fds(t_node *node, t_node *tmp)
{
	while(tmp && tmp->index <= node->index)
	{
		close(tmp->fds[0]);
		close(tmp->fds[1]);
		tmp = tmp->next;
	}
}


void	execute_list_of_cmds(t_node *list_cmd)
{
	int	fk;
	int i;
	int chek;
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
		chek = 0;
		i = 0;
		while(list_cmd->cmd_dt->file[i])
		{
			if(list_cmd->cmd_dt->file[i][0] == '\0' && ft_strcmp("<<", list_cmd->cmd_dt->op[i]))
			{
				chek = 1;
				break ;
			}
			i++;
			// if(list_cmd->cmd_dt->file[i])
		}
		if(chek)
		{
			list_cmd = list_cmd->next;
			continue; 
		}
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
					if(list_cmd->outf_fd == 1)
					{
						list_cmd->outf_fd = list_cmd->fds[1];
						dup2(list_cmd->fds[1], 1);
					}
					if(list_cmd->outf_fd > 2)
						dup2(list_cmd->outf_fd, 1);
					close_fds(list_cmd, tmp);
					if(is_builtin(list_cmd))
					{
						builtins(list_cmd);
					}
					else
					{
						
						check_cmds(list_cmd);
					}
					exit(0);
				}
	
			}
			else
			{
				
				fk = fork();
				if (fk == 0)
				{
					close_fds(list_cmd, tmp);
					if(list_cmd->outf_fd > 2)
						dup2(list_cmd->outf_fd, 1);
					else if (list_cmd->outf_fd == 1)
						dup2(1, list_cmd->outf_fd);
					if(is_builtin(list_cmd))
					{
						builtins(list_cmd);
						
					}
					else
						check_cmds(list_cmd);
					exit(0);
					
				}
				close_all_fds(list_cmd, tmp);
				while (wait(NULL) != -1)
					;
					g_gb.exit_code = 0;
			}
		}
		else
		{

			fk = fork();
			if (fk == 0)
			{
				if(list_cmd->outf_fd > 2)
					dup2(list_cmd->outf_fd, 1);
				if(list_cmd->inf_fd > 2)
					dup2(list_cmd->inf_fd, 0);
				check_cmds(list_cmd);
			}
			else
			{
			// printf("pipe out : %d\npipe in : %d\n", list_cmd->outf_fd, list_cmd->inf_fd);
				if (list_cmd->inf_fd > 2)
					close(list_cmd->inf_fd);
				if (list_cmd->outf_fd > 2)
					close(list_cmd->outf_fd);
			}

			while (wait(NULL) != -1)
					;
			// close(list_cmd->outf_fd);
			
		}
		list_cmd = list_cmd->next;
	}
}
