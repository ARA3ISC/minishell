/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:17:18 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/03 01:58:33 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void      ft_echo(t_node *cmd)
{
    char *cmd_tmp;
    int i;
    int k;
    char *print = NULL;
    int nl = 1; 
    cmd_tmp = &(cmd->new_cmd[4]);
    // if (cmd_tmp[0] == ' ' || cmd_tmp[0] == '<' || cmd_tmp[0] == '>')
    if (cmd_tmp[0] == ' ' || cmd_tmp[0] == '<' || cmd_tmp[0] == '>')
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
            else if(cmd_tmp[i] == '-' && cmd_tmp[i   + 1] == 'n' && (cmd_tmp[i + 2] == 'n' || cmd_tmp[i + 2] == ' ' || cmd_tmp[i + 2] == '\0'))
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
            {
                while(cmd_tmp[i] && cmd_tmp[i] != 39 && cmd_tmp[i] != 34 && cmd_tmp[i] != '<' && cmd_tmp[i] != '>')
                {
                    // printf("char : |%c|\n",cmd_tmp[i]);
                    print = ft_strjoin_char(print, cmd_tmp[i]);
                    i++;
                }
                // if(cmd_tmp[i] == ' ')
                //     i++;
            }
        }   
    }
    if(print) 
    {
        print  = ft_strtrim(print, " ");
        // printf("%s", print);
        ft_putstr_fd(print, cmd->outf_fd);
    }   
    if(nl)
        ft_putstr_fd("\n", cmd->outf_fd);
    free(print);
    // dup2( 1,cmd->outf_fd);
    // close(cmd->outf_fd);
}