/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:20:06 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/07 12:25:04 by maneddam         ###   ########.fr       */
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
