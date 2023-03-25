/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/25 12:19:06 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int		cmds_count(char **cmds)
{
	int i = 0;
	while (cmds[i])
		i++;
	return i;
}

int	**alloc_pipes(char **all_cmds)
{
	int **arr;
	int i = 0;

	arr = malloc(sizeof(int *) * cmds_count(all_cmds));

	while (i < cmds_count(all_cmds))
	{
		arr[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return arr;
}

void	fill_struct(char *cmd)
{
	int i = 0;
	char **all_cmds;
	int **pipes_arr;

	all_cmds = ft_split(cmd, '|');
	pipes_arr = alloc_pipes(all_cmds);
	// TRIM SPACES FROM SIDES
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		ft_lstadd_back(&cmd_struct, ft_lstnew(all_cmds[i], pipes_arr[i]));
		i++;
	}


}

void	syntax_error(char *cmd)
{
	size_t i = 0;
	while (cmd[i])
	{
		if (((i == 0 || i == ft_strlen(cmd) - 1) && cmd[i] == '|'))
			print_error("syntax error near unexpected token `|'");
		if (cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|')
			print_error("syntax error `||'");
		i++;
	}
}

void	signal_received(char s)
{
	if (s == 'D')
	{
		printf(" exit\n");
		exit(0);
	}
}

void	signal_C_received(int signo)
{
	// (void)signo;
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *path;
	char *cmd;

	signal(SIGINT, signal_C_received);


	path = ft_strjoin(env[16], "$ ");
	path = ft_strchr(path, '/');
	while ((cmd = readline(path)) != NULL)
	{
		syntax_error(cmd);
		fill_struct(cmd);
		// printf("%s\n", cmd_struct->cmd);
		// printf("%p\n", cmd_struct->next);



		ft_lstclear(&cmd_struct);
		free(cmd);
	}
	signal_received('D');
}
