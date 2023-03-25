/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/25 15:13:29 by eej-jama         ###   ########.fr       */
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

int help_check_quot(char *string, size_t *i, int qt)
{
    int check;

    check = 1;
    while(string[*i])
    {
        if(string[*i] == qt)
        {
            check = 0;
            break ;
        }
        (*i)++;
    }
    return check;
}

int checking_quots(char c, size_t *i, char *cmd)
{
	int check = 0;
	int qt;
	if(c == 39)
	{
		(*i)++;
		qt = 39;
		check = help_check_quot(cmd, i, qt);
	}
	if(c == 34)
	{
		(*i)++;
		qt = 34;
		check = help_check_quot(cmd, i, qt);
	}
	return check;
}

void	syntax_error(char *cmd)
{
	size_t i = 0;
	int check = 0;
	while (cmd[i])
	{
		check = checking_quots(cmd[i], &i, cmd);
		if(check)
		{
			printf("quot error\n");
			break; 
		}
		else if ((cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|') || cmd[i] == '&' || cmd[i] == '*')
		{
			printf("syntax error\n");
			break;	
		}
		else if (((i == 0 || i == ft_strlen(cmd) - 1) && cmd[i] == '|'))
		{
			printf("syntax error near unexpected token `|'\n");
			break;
		}
		
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char    *get_pwd(char **env)
{
    int i = 0;

    while (env[i])
    {
        if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
            return env[i];
        i++;
    }
    return NULL;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *path;
	char *cmd;

	signal(SIGINT, signal_C_received);

	path = get_pwd(env);
	path = ft_strjoin(path, "$ ");
	path = ft_strchr(path, '/');
	while ((cmd = readline(path)) != NULL)
	{
		syntax_error(cmd);
		fill_struct(cmd);
		add_history(cmd);
		// printf("%s\n", cmd_struct->cmd);
		// printf("%p\n", cmd_struct->next);



		ft_lstclear(&cmd_struct);
		free(cmd);
	}
	signal_received('D');
}
