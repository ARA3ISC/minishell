/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:45:34 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/08 02:33:24 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_one_cmd(t_node *list_cmd)
{
	int	fk;

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
		if (list_cmd->inf_fd > 2)
			close(list_cmd->inf_fd);
		if (list_cmd->outf_fd > 2)
			close(list_cmd->outf_fd);
	}
	wait(&g_gb.exit_code);
	g_gb.exit_code = WEXITSTATUS(g_gb.exit_code);
}

void    execute_last_cmd(t_node *list_cmd, t_node *tmp)
{
	int fk;
	
	fk = fork();
	if (fk == 0)
	{
		close_fds(list_cmd, tmp);
		if(list_cmd->outf_fd > 2)
			dup2(list_cmd->outf_fd, 1);
		else if (list_cmd->outf_fd == 1)
			dup2(1, list_cmd->outf_fd);
		if(is_builtin(list_cmd))
			builtins(list_cmd);
		else
			check_cmds(list_cmd);
		exit(0);
		
	}
	close_all_fds(list_cmd, tmp);
	while (wait(NULL) != -1)
		;
}
void    execute_middle_cmds(t_node *list_cmd, t_node *tmp)
{
	int fk;

	pipe(list_cmd->fds);
	fk = fork();
	if (fk == 0)
	{
		close(list_cmd->fds[0]);
		if(list_cmd->inf_fd == 0 && list_cmd->index > 0)
			list_cmd->inf_fd = list_cmd->fds[0];
		dup2(list_cmd->inf_fd, 0);
		if(list_cmd->outf_fd == 1)
		{
			list_cmd->outf_fd = list_cmd->fds[1];
			dup2(list_cmd->fds[1], 1);
		}
		else if(list_cmd->outf_fd > 2)
			dup2(list_cmd->outf_fd, 1);
			
		close_fds(list_cmd, tmp);
		if(is_builtin(list_cmd))
			builtins(list_cmd);
		else
			check_cmds(list_cmd);
		exit(0);
	}
}

int	is_herdoc(t_node *list_cmd)
{
	int i;

	i = 0;
	while(list_cmd->cmd_dt->file[i])
	{
		if(list_cmd->cmd_dt->file[i][0] == '\0' && ft_strcmp("<<", list_cmd->cmd_dt->op[i]))
			return 1;
		i++;
	}
	return 0;
}

void	execute_all_cmds(t_node *list_cmd, t_node *tmp, int len)
{
	if (len > 1)
	{
		if (list_cmd->index != g_gb.infos->cmd_count - 1)
			execute_middle_cmds(list_cmd, tmp);
		else
			execute_last_cmd(list_cmd, tmp);
	}
	else
		execute_one_cmd(list_cmd);
}
