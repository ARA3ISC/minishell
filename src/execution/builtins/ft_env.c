/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:59:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/29 14:18:27 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(char *full_cmd)
{
    (void)full_cmd;
    t_env *tmp;
    int i;
    tmp = g_gb.my_env;
    i = 0;
    while(tmp)
    {
        printf("%s=", tmp->name);
        if(tmp->value)
            printf("%s\n", tmp->value);
        else
            printf("\n");
        tmp = tmp->next; 
    }
}