/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:28:22 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/29 16:52:29 by eej-jama         ###   ########.fr       */
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
   
}


void builtins(char *full_cmd)
{
    // printf("cmd : %s\n", full_cmd);
    if(!ft_strncmp(full_cmd, "echo", 4) && (full_cmd[4] == ' ' || full_cmd[4] == '<'
        || full_cmd[4] == '>' || full_cmd[4] == '\0'))
        ft_echo(full_cmd);
    else if(!ft_strncmp(full_cmd, "cd", 2) && (full_cmd[2] == ' ' || full_cmd[2] == '<'
        || full_cmd[2] == '>' || full_cmd[2] == '\0'))
        ft_cd(full_cmd);
    else if(!ft_strncmp(full_cmd, "pwd", 3) && (full_cmd[3] == ' ' || full_cmd[3] == '<'
        || full_cmd[3] == '>' || full_cmd[3] == '\0'))
        ft_pwd(full_cmd);
    else if(!ft_strncmp(full_cmd, "exit", 4) && (full_cmd[4] == ' ' || full_cmd[4] == '<'
        || full_cmd[4] == '>' || full_cmd[4] == '\0'))
        ft_exit(full_cmd);
    else if(!ft_strncmp(full_cmd, "export", 6) && (full_cmd[6] == ' ' || full_cmd[6] == '<'
        || full_cmd[6] == '>' || full_cmd[6] == '\0'))
        ft_export(full_cmd);
    else if(!ft_strncmp(full_cmd, "env", 3) && (full_cmd[3] == ' ' || full_cmd[3] == '<'
        || full_cmd[3] == '>' || full_cmd[3] == '\0'))
        ft_env(full_cmd);
    else if(!ft_strncmp(full_cmd, "unset", 5) && (full_cmd[5] == ' ' || full_cmd[5] == '<'
        || full_cmd[5] == '>' || full_cmd[5] == '\0'))
        ft_unset(full_cmd);
    else if(full_cmd[0])
        command_not_found(full_cmd);
    
    
}

// echo (ualu)
// echo -nnnnn. arabi   done
// echo $?