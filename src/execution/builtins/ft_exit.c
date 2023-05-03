/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:26:33 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/03 23:14:14 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

int ft_is_nbr(char *str)
{
    int i = 0;
    
    while (str[i])
    {
        if(!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
       
}

void ft_exit(t_node *full_cmd)
{
    char *cmd_tmp;
    int i = 0;
    char *flags;
    char **split_flags;

    flags = NULL;
    cmd_tmp = &(full_cmd->new_cmd[4]);
    
    while (cmd_tmp[i] && cmd_tmp[i] == 32)
        i++;
    while(cmd_tmp[i])
    {
        if(cmd_tmp[i] && cmd_tmp[i] == 32)
        {
            flags = ft_strjoin_char(flags, '&');
            while (cmd_tmp[i] && cmd_tmp[i] == 32)
                i++;
        }
        
        if (cmd_tmp[i] && (cmd_tmp[i] == '<' || cmd_tmp[i] == '>'))
        {
            i++;
            if (cmd_tmp[i] && (cmd_tmp[i] == '<' || cmd_tmp[i] == '>'))
                i++;
            while (cmd_tmp[i] && cmd_tmp[i] == 32)
                i++;
            while(cmd_tmp[i] && cmd_tmp[i] != 32)
                i++;
        }
        else if(cmd_tmp[i] && cmd_tmp[i] == 34)
        {
            i++;
            while(cmd_tmp[i] && cmd_tmp[i] != 34)
            {
                flags = ft_strjoin_char(flags, cmd_tmp[i]);
                i++;
            }
            i++;
        }
       else  if(cmd_tmp[i] && cmd_tmp[i] == 39)
        {
            i++;
            while(cmd_tmp[i] && cmd_tmp[i] != 39)
            {
                flags = ft_strjoin_char(flags, cmd_tmp[i]);
                i++;
            }
            i++;
        }
        else
        {
            flags = ft_strjoin_char(flags, cmd_tmp[i]);
            i++;
        }
    }
    split_flags = ft_split(flags, '&');
    i = 0;
    while(split_flags[i])
        i++;
    if(!ft_is_nbr(split_flags[0]))
    {
        ft_putstr_fd("minishell: exit: numeric argument required", full_cmd->outf_fd);
        ft_putstr_fd("\n", full_cmd->outf_fd);
        exit(255);
    }
    if(ft_is_nbr(split_flags[0]) && i > 1)
    {
        ft_putstr_fd("minishell: exit: too many arguments", full_cmd->outf_fd);
        ft_putstr_fd("\n", full_cmd->outf_fd);
    }
    else if (ft_is_nbr(split_flags[0]) && i == 1)
        exit(ft_atoi(split_flags[0]));
    else
        exit(0);
}
