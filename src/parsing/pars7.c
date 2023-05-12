/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:54:35 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:07:24 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output_redirections(t_node *list_cmd, int i)
{
	int		fd;
	char	*file;

	fd = -2;
	file = NULL;
	if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">"))
		overridee(list_cmd, file, i);
	else if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">>"))
	{
		file = expanded_file_name(list_cmd, i);
		if (file)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_APPEND,
					0666);
		list_cmd->outf_fd = fd;
	}
	if (fd == -1)
	{
		print_error("minishell: : No such file or directory", 103);
		return (0);
	}
	return (1);
}

int	input_redirections(t_node *list_cmd, int i)
{
	int	fd;

	if (!ft_strcmp(list_cmd->cmd_dt->op[i], "<"))
	{
		fd = open(list_cmd->cmd_dt->file[i], O_RDWR);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n",
				list_cmd->cmd_dt->file[i]);
			print_error(NULL, 1);
			return (0);
		}
		list_cmd->inf_fd = fd;
	}
	return (1);
}

int	open_files(t_node *list_cmd)
{
	int	i;
	int	rd;

	rd = 1;
	i = 0;
	while (list_cmd->cmd_dt->file[i])
	{
		rd = output_redirections(list_cmd, i);
		if (rd)
			rd = input_redirections(list_cmd, i);
		if (!rd)
			break ;
		i++;
	}
	return (rd);
}
