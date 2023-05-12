/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils9.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:13:48 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:12:28 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_count(char *cmd)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
		{
			i++;
			help_check_quote(cmd, &i, 39);
		}
		if (cmd[i] && cmd[i + 1] && cmd[i] == '$' && (cmd[i + 1] == '?'
				|| ft_isalnum(cmd[i + 1])))
			len++;
		i++;
	}
	return (len);
}

void	read_from_herdoc(char *eof, char *input, int fd1, char *coted)
{
	char	*rd;
	char	*result;

	result = NULL;
	while (1)
	{
		rd = readline("herdoc> ");
		if (!rd)
			exit(0);
		if (!ft_strcmp(rd, eof))
		{
			if (coted[0] == '0')
			{
				result = expend_herdocc(input);
				write(fd1, result, ft_strlen(result) * sizeof(char));
				free(result);
			}
			else
				write(fd1, input, ft_strlen(input) * sizeof(char));
			free(input);
			exit(0);
		}
		input = ft_strjoin2(input, rd);
		input = ft_strjoin(input, "\n");
	}
}

int	get_len_vars(char *input)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] && (input[i + 1] == '?'
				|| ft_isalnum(input[i + 1])))
			len++;
		i++;
	}
	return (len);
}
