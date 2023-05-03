/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:28:22 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/02 16:01:17 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void command_not_found(char *full_cmd)
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

}


void builtins(t_node *full_cmd)
{
	// if(full_cmd->outf_fd > 2)
	// {
	// 	// close(full_cmd->fds[0]);
	// 	dup2(full_cmd->outf_fd, 1);
	// }

	if(!ft_strncmp(full_cmd->new_cmd, "echo", 4) && (full_cmd->new_cmd[4] == ' ' || full_cmd->new_cmd[4] == '<'
		|| full_cmd->new_cmd[4] == '>' || full_cmd->new_cmd[4] == '\0'))
		ft_echo(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "cd", 2) && (full_cmd->new_cmd[2] == ' ' || full_cmd->new_cmd[2] == '<'
		|| full_cmd->new_cmd[2] == '>' || full_cmd->new_cmd[2] == '\0'))
		ft_cd(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "pwd", 3) && (full_cmd->new_cmd[3] == ' ' || full_cmd->new_cmd[3] == '<'
		|| full_cmd->new_cmd[3] == '>' || full_cmd->new_cmd[3] == '\0'))
		ft_pwd(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "exit", 4) && (full_cmd->new_cmd[4] == ' ' || full_cmd->new_cmd[4] == '<'
		|| full_cmd->new_cmd[4] == '>' || full_cmd->new_cmd[4] == '\0'))
		ft_exit(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "export", 6) && (full_cmd->new_cmd[6] == ' ' || full_cmd->new_cmd[6] == '<'
		|| full_cmd->new_cmd[6] == '>' || full_cmd->new_cmd[6] == '\0'))
		ft_export(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "env", 3) && (full_cmd->new_cmd[3] == ' ' || full_cmd->new_cmd[3] == '<'
		|| full_cmd->new_cmd[3] == '>' || full_cmd->new_cmd[3] == '\0'))
		ft_env(full_cmd);
	else if(!ft_strncmp(full_cmd->new_cmd, "unset", 5) && (full_cmd->new_cmd[5] == ' ' || full_cmd->new_cmd[5] == '<'
		|| full_cmd->new_cmd[5] == '>' || full_cmd->new_cmd[5] == '\0'))
		ft_unset(full_cmd);
	else if(full_cmd->new_cmd[0])
		command_not_found(full_cmd->new_cmd);
	// if(full_cmd->outf_fd > 2)
	// {
	// 	dup2(1, full_cmd->outf_fd);
	// 	close(full_cmd->outf_fd);
	// }
	// while(g_gb.my_env)
	// {
	// 	printf("name : %s\nvalue : %s\n", g_gb.my_env->name, g_gb.my_env->value);
	// 	g_gb.my_env = g_gb.my_env->next;
	// }

	
}

// echo (ualu)
// echo -nnnnn. arabi   done
// echo $?
