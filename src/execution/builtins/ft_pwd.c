/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:40:50 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:38 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void ft_pwd(t_node *full_cmd)
{
    (void)full_cmd;
    char tab[2000];
    if (getcwd(tab, sizeof(tab)) != NULL) {
       ft_putstr_fd(tab, full_cmd->outf_fd);
       ft_putstr_fd("\n", full_cmd->outf_fd);
   } else {
       perror("getcwd() error");
   }
    g_gb.exit_code = 0;

}