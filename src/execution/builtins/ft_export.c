/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:33:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/03 00:03:11 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

int name_is_exist(char *name)
{
    t_env *tmp;
    
    tmp = g_gb.my_env;            
    while(tmp)
    {
        if(!ft_strcmp(name, tmp->name))
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void ft_export(t_node *full_cmd)
{
    t_env *tmp;
    char *name = NULL;
    char *value = NULL;
	char *cmd;
	int i;
    int plus = 0;
    i = 0;

	cmd = &(full_cmd->new_cmd[6]);
	while(cmd[i])
    {
        if (cmd[i] == '>' || cmd[i] == '<')
        {
            i++;
            if(cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
                i++;
            while(cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
                i++;
            while(cmd[i] && cmd[i] != 32 && cmd[i] != '\t')
                i++;
        }
        else if (cmd[i] == ' ')
            while(cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
                i++;
        else
        {
            while(cmd[i] && cmd[i] != '+' && cmd[i] != '=' && cmd[i] != ' ')
            {
                if(cmd[i] == 34 || cmd[i] == 39)
                    i++;
                else
                    name = ft_strjoin_char(name, cmd[i++]);
            }
            // printf("char : |%c|\n", cmd[i]);
            if(cmd[i] == ' ' || cmd[i] == '\0')
            {
                free(name);
                break;
            }
            else 
            {
                if(cmd[i] == '+')
                {
                    i++;
                    plus = 1;
                    if(cmd[i] != '=')
                    {
                        ft_putstr_fd("not a valid identifier", full_cmd->outf_fd );
                        ft_putstr_fd("\n", full_cmd->outf_fd );
                        return;
                    }
                }
                i++;
                while(cmd[i] && cmd[i] != ' ')
                {
                    if(cmd[i] == 34)
                    {
                        i++;
                        while(cmd[i] && cmd[i] != 34 )
                        {
                            value = ft_strjoin_char(value, cmd[i]);
                            i++;
                        }
                        i++;
                    } 
                    else if(cmd[i] == 39)
                    {
                        i++;
                        while(cmd[i] && cmd[i] != 39 )
                        {
                            value = ft_strjoin_char(value, cmd[i]);
                            i++;
                        }
                        i++;
                    }
                    else 
                        value = ft_strjoin_char(value, cmd[i++]);
                }
                
                tmp = g_gb.my_env;
                if(name_is_exist(name))
                {
                    while(tmp)
                    {
                        if(!ft_strcmp(name, tmp->name))
                        {
                            if(plus)
                                tmp->value = ft_strjoin(tmp->value, value);
                            else
                                tmp->value = value;
                        }
                        tmp = tmp->next;
                    }
                }
                else
                {
                    
                    ft_lstadd_back_env(&tmp, ft_lstnew_env(name, value));
                    
                    
                }
                name = NULL;
                value =  NULL;
                plus = 0;
            }
            
        }
    }
    
}