/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:20:06 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/26 18:13:36 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char const *argv[], char **env)
{
    (void)argc;
	(void)argv;
    t_node *list_cmd = NULL;
    parsing(env, list_cmd);
    
    
    return 0;
}
