/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:20:06 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:13:00 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char **env)
{
	t_node	*list_cmd;

	(void)argc;
	(void)argv;
	list_cmd = NULL;
	parsing(env, list_cmd);
	return (0);
}
