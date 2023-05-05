/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:33:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:32 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void display_export(t_node *full_cmd)
{
    t_env *tmp;
     tmp = g_gb.my_export;
     
    while(tmp)
    {
        // printf("equal : %d\n", tmp->equal);
		// printf("pipe out : %d\npipe in : %d\n", full_cmd->outf_fd, full_cmd->inf_fd);

        ft_putstr_fd("declare -x ", full_cmd->outf_fd);
        ft_putstr_fd(tmp->name, full_cmd->outf_fd);
        
        if(tmp->equal)
        {
            ft_putstr_fd("=\"", full_cmd->outf_fd);
            if(tmp->value)
                ft_putstr_fd(tmp->value, full_cmd->outf_fd);
            ft_putstr_fd("\"\n", full_cmd->outf_fd);
        
        }
        else
            ft_putstr_fd("\n", full_cmd->outf_fd);
        

        
        tmp = tmp->next;
    }
}



int name_is_exist_in_env(char *name)
{
    t_env *tmp;
    // if(!name)
    //     return 0;
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

int name_is_exist_in_export(char *name)
{
    t_env *tmp;
    // if(!name)
    //     return 0;
    tmp = g_gb.my_export;            
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
    t_env *tmp2;
    char *name = NULL;
    char *value = NULL;
	char *cmd;
	int i;
	// int check = 0;
    int plus = 0;
    i = 0;

	cmd = &(full_cmd->cmd[6]);
    if(!cmd[0])
        display_export(full_cmd);
	while(cmd[i])
    {
        // printf("char : |%c|\n", cmd[i]);
        if (cmd[i] == '>' || cmd[i] == '<')
        {
            i++;
            if(cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
                i++;
            while(cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
                i++;
            if(cmd[i] && cmd[i] == 34)
            {
                i++;
                while(cmd[i] && cmd[i] != 34)
                    i++;
                i++;
            }
            else if(cmd[i] && cmd[i] == 39)
            {
                i++;
                while(cmd[i] && cmd[i] != 39)
                    i++;
                i++;
            }
            else
                while(cmd[i] && cmd[i] != 32 && cmd[i] != '\t')
                    i++;
            if(!cmd[i])
                 display_export(full_cmd);
        }
        else if (cmd[i] == ' ')
            while(cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
                i++;
        else
        {
            while(cmd[i] && cmd[i] != '+' && cmd[i] != '=' && cmd[i] != ' ')
            {
                        // printf("char : |%c|\n", cmd[i]);
                if(cmd[i] == 34)
                {
                    i++;
                    while(cmd[i] && cmd[i] != 34)
                    {
                        if(cmd[i] == 32 ||  !ft_isalnum(cmd[i]))
                        {
                            ft_putstr_fd("minishell: export: not a valid identifier", full_cmd->outf_fd);
                            ft_putstr_fd("\n", full_cmd->outf_fd);
                            return ; 
                        }
                        name = ft_strjoin_char(name, cmd[i++]);
                        
                    }
                    i++;
                }
                else if(cmd[i] == 39 )
                {
                    i++;
                    while(cmd[i] && cmd[i] != 39)
                    {
                        if(cmd[i] == 32 ||  !ft_isalnum(cmd[i]))
                        {
                            ft_putstr_fd("minishell: export: not a valid identifier", full_cmd->outf_fd);
                            ft_putstr_fd("\n", full_cmd->outf_fd);
                            return ; 
                        }
                        name = ft_strjoin_char(name, cmd[i++]);
                        
                    }
                    i++;
                }
                else
                {
                    if(!ft_isalnum(cmd[i]))
                    {
                        ft_putstr_fd("minishell: export: not a valid identifier", full_cmd->outf_fd);
                            ft_putstr_fd("\n", full_cmd->outf_fd);
                            return ; 
                    }
                    name = ft_strjoin_char(name, cmd[i++]);
                }
            }
            if(cmd[i] == ' ' || cmd[i] == '\0')
            {
                tmp2 = g_gb.my_export;
                if(!name_is_exist_in_export(name))
                    ft_lstadd_back_env(&tmp2, ft_lstnew_env(name, "" , 0, existe_spaces("")));
                if(cmd[i])    
                    i++;
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
                while(cmd[i] && cmd[i] != 32)
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
                tmp2 =  g_gb.my_export;
                if(name_is_exist_in_env(name))
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
                    ft_lstadd_back_env(&tmp, ft_lstnew_env(name, value , 1, existe_spaces(value)));
                    ft_lstadd_back_env(&tmp2, ft_lstnew_env(name, value, 1, existe_spaces(value)));
                    
                    
                }
            }
                name = NULL;
                value =  NULL;
                plus = 0;
        }
    }
    g_gb.exit_code = 0;
    
}


