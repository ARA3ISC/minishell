/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:25:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 17:11:03 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_error(int error, int i, char *cmd, int check)
{
	while (!error && cmd[i])
	{
		check = checking_quotes(cmd[i], &i, cmd);
		if (check)
			return (print_error("quote error", 101));
		if (cmd[i] == '(' || cmd[i] == ')')
			return (print_error("syntax error near unexpected token", 102));
		if ((cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|') || cmd[i] == '&'
			|| cmd[i] == '\\' || cmd[i] == ';')
			return (print_error("syntax error", 103));
		if (((i == 0 || i == ft_strlen(cmd) - 1) && cmd[i] == '|'))
			return (print_error("syntax error near unexpected token `|'", 258));
		i++;
	}
	return (0);
}

int	syntax_error(char *cmd)
{
	int	i;
	int	check;
	int	error;
	int	len;

	i = 0;
	check = 0;
	error = 0;
	len = ft_strlen(cmd) - 1;
	while (len > 0 && (cmd[len] == 32 || cmd[len] == '\t'))
		len--;
	if (len >= 0 && cmd[len] == '|')
		return (print_error("syntax error near unexpected token `|'", 258));
	error = checking_redirection_in_the_last(cmd);
	if (!error)
		error = help_error(error, i, cmd, check);
	return (error);
}

int	check_redirection_syntax(char *cmd)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '<'))
			return (print_error("syntax error", 258));
		if (cmd[i + 1] && cmd[i + 2] && ((cmd[i] == '>' && cmd[i + 1] == '>'
					&& cmd[i + 2] == '>') || (cmd[i] == '<' && cmd[i + 1] == '<'
					&& cmd[i + 2] == '<')))
			return (print_error("syntax error", 258));
		i++;
	}
	return (error);
}
