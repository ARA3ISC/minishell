/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:25:53 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:16 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_node *full_cmd)
{
	char *path = NULL;
	char *cmd_tmp;
	int i;

	cmd_tmp = &(full_cmd->new_cmd[2]);
	if (cmd_tmp[0] == ' ')
	{
			// printf("mmmmmmmmm\n");
		i = 0;
		while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
			i++;
		while (cmd_tmp[i])
		{
			if (cmd_tmp[i] == 34)
			{
				i++;
				while (cmd_tmp[i] && cmd_tmp[i] != 34)
				{
					path = ft_strjoin_char(path, cmd_tmp[i]);
					i++;
				}
				i++;
			}
			else if (cmd_tmp[i] == 39)
			{
				i++;
				while (cmd_tmp[i] && cmd_tmp[i] != 39)
				{
					path = ft_strjoin_char(path, cmd_tmp[i]);
					i++;
				}
				i++;
			}
			else if (cmd_tmp[i] == '<' || cmd_tmp[i] == '>')
			{
				i++;
				if (cmd_tmp[i] == '>')
					i++;
				while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
					i++;
				while (cmd_tmp[i] && cmd_tmp[i] != 32 && cmd_tmp[i] != '\t')
					i++;
				while (cmd_tmp[i] && (cmd_tmp[i] == 32 || cmd_tmp[i] == '\t'))
					i++;
			}
			else
				path = ft_strjoin_char(path, cmd_tmp[i++]);
		}
	}
	// printf("my path : |%s|\n", path);
	// exit(0);
	if (chdir(path) == -1)
		perror("error change directory");
    g_gb.exit_code = 0;
	
}