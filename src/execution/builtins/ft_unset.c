/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:52:47 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/01 09:50:50 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void remove_it(char *name)
{
    t_env *tmp;
    t_env *to_destroy;
    
    tmp = g_gb.my_env;
    while(tmp)
    {
        if(tmp->next && !ft_strcmp(name, tmp->next->name))
        {
            to_destroy = tmp->next;
            tmp->next = tmp->next->next;
            free(to_destroy);
        }
        tmp = tmp->next;
    }
}

void ft_unset(char *full_cmd)
{
    // t_env *tmp;
	char *cmd;
    char *name = NULL;
	int i;
    i = 0;

	cmd = &full_cmd[5];
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
            while(cmd[i] && cmd[i] != ' ')
            {
                if(cmd[i] == 34)
                {
                    i++;
                    while(cmd[i] && cmd[i] != 34 )
                    {
                        name = ft_strjoin_char(name, cmd[i]);
                        i++;
                    }
                    i++;
                } 
                else if(cmd[i] == 39)
                {
                    i++;
                    while(cmd[i] && cmd[i] != 39 )
                    {
                        name = ft_strjoin_char(name, cmd[i]);
                        i++;
                    }
                    i++;
                }
                else 
                    name = ft_strjoin_char(name, cmd[i++]);
            }
            // printf("--- %s\n", name);
            if(name_is_exist(name))
                remove_it(name);
            name = NULL;
        }
    }
    
}