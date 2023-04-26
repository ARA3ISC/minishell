/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/26 18:14:25 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void execution(t_node *list_cmd)
{
    while(list_cmd)
    {
        printf("%s\n", list_cmd->new_cmd);
        list_cmd = list_cmd->next;
    }
}