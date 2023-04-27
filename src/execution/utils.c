/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:08:24 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/27 13:33:00 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(t_node *list_cmd, char *built)
{
	if ((!ft_strncmp(list_cmd->new_cmd, built, ft_strlen(built)) && list_cmd->new_cmd[ft_strlen(built) + 1] != '<')
		|| (!ft_strncmp(list_cmd->new_cmd, built, ft_strlen(built)) && list_cmd->new_cmd[ft_strlen(built) + 1]  != '>'))
		return 1;
	return 0;
}

int		is_builtin(t_node *list_cmd)
{

	if ((is_redirection(list_cmd, "echo") || is_redirection(list_cmd, "cd")
			|| is_redirection(list_cmd, "pwd") || is_redirection(list_cmd, "export")
			|| is_redirection(list_cmd, "unset") || is_redirection(list_cmd, "env")
			|| is_redirection(list_cmd, "exit")))
			return 1;
	return 0;
}
