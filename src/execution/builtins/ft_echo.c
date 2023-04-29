/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:17:18 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/28 22:30:59 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(char *cmd)
{
    char *cmd_tmp;
    int i;
    int k;
    char *print = NULL;
    int nl = 1; 

    cmd_tmp = &cmd[4];
    if (cmd_tmp[0] == ' ')
    {
        i = 0;
        while(cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] =='\t'))
            i++;
        while(cmd_tmp[i])
        {
            if(cmd_tmp[i] == 34)
            {
                i++;
                while(cmd_tmp[i] && cmd_tmp[i] != 34 )
                {
                    print = ft_strjoin_char(print, cmd_tmp[i]);
                    i++;
                }
                i++;
            }
            else if(cmd_tmp[i] == 39)
            {
                i++;
                while(cmd_tmp[i] && cmd_tmp[i] != 39 )
                {
                    print = ft_strjoin_char(print, cmd_tmp[i]);
                    i++;
                }
                i++;
            }
            else if(cmd_tmp[i] == '-' && cmd_tmp[i + 1] == 'n' && (cmd_tmp[i + 2] == 'n' || cmd_tmp[i + 2] == ' ' || cmd_tmp[i + 2] == '\0'))
            {
                k = i;
                i = i + 2;
                while(cmd_tmp[i] && cmd_tmp[i] == 'n')
                    i++;
                if(cmd_tmp[i] && cmd_tmp[i] != ' ')
                {
                    print = ft_strjoin_char(print, cmd_tmp[k]);
                    i = k + 1;
                }
                else
                    nl = 0;
                while(cmd_tmp[i] && cmd_tmp[i] == ' ')
                    i++;
                
            }
            else if (cmd_tmp[i] == '<' || cmd_tmp[i] == '>')
            {
                i++;
                if(cmd_tmp[i] == '>')
                    i++;
                while(cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] =='\t'))
                    i++;
                while(cmd_tmp[i] && cmd_tmp[i] != 32 && cmd_tmp[i] !='\t')
                    i++;
                while(cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] =='\t'))
                    i++;
            }
            else
                print = ft_strjoin_char(print, cmd_tmp[i++]);
        }   
    }
    if(print)    
        printf("%s", print);
    if(nl)
        printf("\n");
}