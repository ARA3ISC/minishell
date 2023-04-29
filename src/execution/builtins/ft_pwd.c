/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:40:50 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/29 11:04:46 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void ft_pwd(char *full_cmd)
{
    (void)full_cmd;
    char tab[2000];
    if (getcwd(tab, sizeof(tab)) != NULL) {
       printf("%s\n", tab);
   } else {
       perror("getcwd() error");
   }
}