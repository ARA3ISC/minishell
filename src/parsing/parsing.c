/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/26 14:35:47 by maneddam         ###   ########.fr       */
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
	if (check_whitespaces(all_cmds) && cmd[0])
	{
		printf("Syntax error\n");
		return ;
	}
	pipes_arr = alloc_pipes(all_cmds);
	// TRIM SPACES FROM SIDES
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		ft_lstadd_back(&s, ft_lstnew(all_cmds[i], pipes_arr[i]));
		i++;
	}
}

int help_check_quote(char *string, size_t *i, int qt)
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

int checking_quotes(char c, size_t *i, char *cmd)
{
	int check = 0;
	int qt;
	if(c == 39)
	{
		(*i)++;
		qt = 39;
		check = help_check_quote(cmd, i, qt);
	}
	if(c == 34)
	{
		(*i)++;
		qt = 34;
		check = help_check_quote(cmd, i, qt);
	}
	return check;
}

void	syntax_error(char *cmd)
{
	size_t i = 0;
	int check = 0;
	while (cmd[i])
	{
		check = checking_quotes(cmd[i], &i, cmd);
		if(check)
		{
			printf("quote error\n");
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
		printf("exit\n");
		exit(0);
	}
}

void	signal_C_received(int signo)
{
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
    return (NULL);
}

void	check_redirection_syntax()
{
	int i;
	while (s)
	{
		i = 0;
		while (s->cmd[i])
		{
			if (s->cmd[i + 1]  && ((s->cmd[i] == '<' && s->cmd[i + 1] == '>')
				|| (s->cmd[i] == '>' && s->cmd[i + 1] == '<')))
				printf("syntax error near unexpected token `%c'\n", s->cmd[i]);
			if (s->cmd[i + 1] && s->cmd[i + 2] && ((s->cmd[i] == '>' && s->cmd[i + 1] == '>' && s->cmd[i + 2] == '>')
				|| (s->cmd[i] == '<' && s->cmd[i + 1] == '<' && s->cmd[i + 2] == '<')))
				printf("syntax error near unexpected token `%c'\n", s->cmd[i]);
			i++;
		}
		s = s->next;
	}
}

void	banner()
{
	printf("\n");
	printf(RED"   *     (        )  (    (        )       (     (    \n");
	printf(" (  `    )\\ )  ( /(  )\\ ) )\\ )  ( /(       )\\ )  )\\ ) \n");
	printf(" )\\))(  (()/(  )\\())(()/((()/(  )\\()) (   (()/( (()/( \n");
	printf("((_)()\\  /(_))((_)\\  /(_))/(_))((_)\\  )\\   /(_)) /(_))\n");
	printf("(_()((_)(_))   _((_)(_)) (_))   _((_)((_) (_))  (_))  \n"GREEN);
	printf("|  \\/  ||_ _| | \\| ||_ _|/ __| | || || __|| |   | |   \n");
	printf("| |\\/| | | |  | .` | | | \\__ \\ | __ || _| | |__ | |__ \n");
	printf("|_|  |_||___| |_|\\_||___||___/ |_||_||___||____||____|\n"RESET);
	printf("\n");
}

void	get_details(t_node *s)
{
	// t_cmd *detailed_cmd;
	// char *op;
	int i = 0;

	// detailed_cmd = malloc(sizeof(t_cmd) * 3);
	while (s->cmd[i])
	{
		if (s->cmd[i] == '>' || s->cmd[i] == '<')
		{
			// printf(">>>>>>>>\n");
			s->cmd_dt->op = malloc(sizeof(char) * 3);
			s->cmd_dt->op[0] = s->cmd[i];
			s->cmd[i] = '$';
			i++;
			if (s->cmd[i] && (s->cmd[i] == '<' || s->cmd[i] == '>'))
			{
				if (s->cmd[i] == '<')
					s->cmd_dt->op[1] = '<';
				else
					s->cmd_dt->op[1] = '>';
				s->cmd[i] = 32;
				s->cmd_dt->op[2] = '\0';
			}
			else
				s->cmd_dt->op[1] = '\0';
		}
		i++;
	}
	printf("\n*******\n");
	// s->cmd_dt->cmd = s->cmd;
}

void	detail_cmd()
{
	t_node *tmp;

	tmp = s;
	// printf("op : %s\n", s->cmd_dt->op);
	// while (1);


	s->cmd_dt = malloc(sizeof(t_cmd) * 3);
	// s->cmd_dt->op = malloc(sizeof(char) * 3);
	while (tmp)
	{
		get_details(tmp);
		printf("cmd : %s\n", tmp->cmd_dt->cmd);
		printf("op : %s\n", tmp->cmd_dt->op);
		printf("-------\n");
		tmp = tmp->next;
	}

}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *path;
	char *cmd;

	signal(SIGINT, signal_C_received);
	banner();
	path = get_pwd(env);
	path = ft_strjoin(path, "$ ");
	if (!path)
		path = "$ ";
	else
		path = ft_strchr(path, '/');
	while ((cmd = readline(path)) != NULL)
	{
		syntax_error(cmd);
		check_redirection_syntax();

		fill_struct(cmd);
		detail_cmd();


		add_history(cmd);


		ft_lstclear(&s);
		free(cmd);
	}
	signal_received('D');
}
