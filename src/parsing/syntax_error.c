/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:25:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/30 15:11:17 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(char *cmd)
{
	int i = 0;
	int check = 0;
	int error;
	error = 0;

	error = checking_redirection_in_the_last(cmd);
	while (!error &&  cmd[i])
	{
		check = checking_quotes(cmd[i], &i, cmd);
		if(check)
		{
			error = print_error("quote error", 101);
			break;
		}
		if ((cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|') || cmd[i] == '&' || cmd[i] == '*' || cmd[i] == '\\')
		{
			error = print_error("syntax error", 102);
			break;
		}
		if (((i == 0 || i == ft_strlen(cmd) - 1) && cmd[i] == '|'))
		{
			error = print_error("syntax error near unexpected token `|'", 258);
			break;
		}
		i++;
	}
	return error;
}

int	check_redirection_syntax(char *cmd)
{
	int i;
	int error;
	i = 0;
	error = 0;
	while (cmd[i])
	{
		if (cmd[i + 1]  && ((cmd[i] == '<' && cmd[i + 1] == '>')
			|| (cmd[i] == '>' && cmd[i + 1] == '<')))
		{
			error = print_error("syntax error", 258);
			break;
		}
		if (cmd[i + 1] && cmd[i + 2] && ((cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] == '>')
			|| (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == '<')))
		{
			error = print_error("syntax error", 258);
			break;
		}
		i++;
	}
	return error;
}
