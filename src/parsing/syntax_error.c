/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:25:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/29 16:32:27 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *cmd)
{
	size_t i = 0;
	int check = 0;

	checking_redirection_in_the_last(cmd);
	while (cmd[i])
	{
		check = checking_quotes(cmd[i], &i, cmd);
		if(check)
		{
			print_error("quote error", 101);
			break;
		}
		if ((cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|') || cmd[i] == '&' || cmd[i] == '*' || cmd[i] == '\\')
		{
			print_error("syntax error", 102);
			break;
		}
		if (((i == 0 || i == ft_strlen(cmd) - 1) && cmd[i] == '|'))
		{
			print_error("syntax error near unexpected token `|'", 258);
			break;
		}
		i++;
	}

}

void	check_redirection_syntax()
{
	t_node *tmp = s;
	int i;
	tmp = s;
	while (s)
	{
		i = 0;
		while (s->cmd[i])
		{
			if (s->cmd[i + 1]  && ((s->cmd[i] == '<' && s->cmd[i + 1] == '>')
				|| (s->cmd[i] == '>' && s->cmd[i + 1] == '<')))
				print_error("syntax error", 258);
			if (s->cmd[i + 1] && s->cmd[i + 2] && ((s->cmd[i] == '>' && s->cmd[i + 1] == '>' && s->cmd[i + 2] == '>')
				|| (s->cmd[i] == '<' && s->cmd[i + 1] == '<' && s->cmd[i + 2] == '<')))
				print_error("syntax error", 258);
			i++;
		}
		s = s->next;
	}
	s = tmp;
}
