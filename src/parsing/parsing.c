/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/28 12:56:45 by maneddam         ###   ########.fr       */
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

char **spliting_by_pipe(char *cmd)
{
	// int i = 0;
	char **all_cmds;
	// while(cmd[i])
	// {
	// 	if(cmd[i] == 39)
	// 	{
	// 		i++;
	// 		while(cmd[i] != 39)
	// 			i++;
	// 		i++;
	// 	}
	// 	if(cmd[i] && cmd[i] == 34)
	// 	{
	// 		i++;
	// 		while(cmd[i] != 34)
	// 			i++;
	// 		i++;
	// 	}
	// 	// if(cmd[i] && cmd[i] == '|') // ! fiha mushkil fhad les cas (| dsfdf) (fadfa |) (sddf || dff)
	// 	// 	cmd[i] = '$';
	// 	i++;
	// }
	all_cmds = ft_split(cmd, '|');
	return all_cmds;
}

int	fill_struct(char *cmd)
{
	int i = 0;
	char **all_cmds;
	int **pipes_arr;
	char *cmd_tmp;
	cmd_tmp = cmd;

	all_cmds = spliting_by_pipe(cmd_tmp);
	if (!all_cmds[0])
		return 1;
	if (check_whitespaces(all_cmds))
	{
		print_error("syntax error near unexpected token `|'", 258);
		//! hna khass n nssetiw exit code l 0 ms rh lvariable li f struct baqi mamallocyinsh lih so tatsegfaulty
		return 1;
	}
	pipes_arr = alloc_pipes(all_cmds);
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		if(!all_cmds[i][0])
			print_error("syntax error near unexpected token `|'", 101);// 3aaaaaaabi viifie hna l exit status ach khaso ykon !!!!!!!!!!!!!!!!!!!
		ft_lstadd_back(&s, ft_lstnew(all_cmds[i], pipes_arr[i]));
		i++;
	}
	return 0;
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

void checking_redirection_in_the_last(char *cmd)
{
	size_t i = ft_strlen(cmd);
	i--;
	while(cmd[i] == ' ')
		i--;
	if(cmd[i] == '>' || cmd[i] == '<')
		print_error("syntax error", 258); // 3aaaaaaabi viifie hna l exit status ach khaso ykon !
}

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
		if ((cmd[i + 1] && cmd[i] == '|' && cmd[i + 1] == '|') || cmd[i] == '&' || cmd[i] == '*')
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

// void	banner()
// {
// 	printf("\n");
// 	printf(GREEN"\t╔╦╗╦╔╗╔╔═╗╦ ╦╔═╗╦  ╦  \n");
// 	printf("\t║║║║║║║╚═╗╠═╣║╣ ║  ║  \n");
// 	printf("\t╩ ╩╩╝╚╝╚═╝╩ ╩╚═╝╩═╝╩═╝\n"RESET);
// }

void	banner()
{
	printf("\n");
	printf(GREEN"\t|███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██| \n");
	printf("\t|████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██|  \n");
	printf("\t|██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██|\n");
	printf("\t|██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██| \n");
	printf("\t|██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████|\n"RESET);
	printf("\n");
}

// void	banner()
// {
// 	printf("\n");
// 	printf(RED"\t   *     (        )  (    (        )       (     (    \n");
// 	printf("\t (  `    )\\ )  ( /(  )\\ ) )\\ )  ( /(       )\\ )  )\\ ) \n");
// 	printf("\t )\\))(  (()/(  )\\())(()/((()/(  )\\()) (   (()/( (()/( \n");
// 	printf("\t((_)()\\  /(_))((_)\\  /(_))/(_))((_)\\  )\\   /(_)) /(_))\n");
// 	printf("\t(_()((_)(_))   _((_)(_)) (_))   _((_)((_) (_))  (_))  \n"GREEN);
// 	printf("\t|  \\/  ||_ _| | \\| ||_ _|/ __| | || || __|| |   | |   \n");
// 	printf("\t| |\\/| | | |  | .` | | | \\__ \\ | __ || _| | |__ | |__ \n");
// 	printf("\t|_|  |_||___| |_|\\_||___||___/ |_||_||___||____||____|\n"RESET);
// 	printf("\n");
// }

void	get_details(t_node *tmp)
{
	char **tab;

	int i = 0;
	int j = 0;
	while (tmp->cmd[i])
	{
		if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
		{

			if (tmp->cmd[i + 1] && (tmp->cmd[i + 1] == '<' || tmp->cmd[i + 1] == '>'))
				tmp->cmd_dt->op[j] = malloc(sizeof(char) * 3);
			else
				tmp->cmd_dt->op[j] = malloc(sizeof(char) * 2);
			tmp->cmd_dt->op[j][0] = tmp->cmd[i];
			tmp->cmd[i] = '$';
			if (tmp->cmd[i + 1] && (tmp->cmd[i + 1] == '<' || tmp->cmd[i + 1] == '>'))
			{
				if (tmp->cmd[i + 1] == '<')
					tmp->cmd_dt->op[j][1] = '<';
				else
					tmp->cmd_dt->op[j][1] = '>';
				tmp->cmd[i + 1] = 32;
				tmp->cmd_dt->op[j][2] = '\0';
			}
			else
				tmp->cmd_dt->op[j][1] = '\0';
			j++;
		}
		i++;
	}
	tmp->cmd_dt->op[j] = NULL;
	tab = ft_split(tmp->cmd, '$');
	tmp->cmd_dt->cmd = tmp->cmd;

}

void	detail_cmd()
{
	t_node *tmp;

	tmp = s;
	while (tmp)
	{

		tmp->cmd_dt = malloc(sizeof(t_cmd));
		tmp->cmd_dt->op = malloc(sizeof(char *) * 6);
		get_details(tmp);
		tmp = tmp->next;
	}

}

int	count_op(char *cmd)
{
	int i = 0;
	int count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	count_pipes(char *cmd)
{
	int i = 0;
	int count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			count++;
		}
		i++;
	}
	return (count);
}

void	get_number_of_tokens(char *full_cmd)
{
	t_node *tmp;

	tmp = s;
	while (s)
	{
		s->infos = malloc(sizeof(t_info));
		s->infos->op_count = count_op(s->cmd);

		s->infos->pipe_count = count_pipes(full_cmd);
		s->infos->cmd_count = s->infos->pipe_count + 1;
		s = s->next;
	}
	s = tmp;
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *path;
	char *full_cmd;

	banner();
	signal(SIGINT, signal_C_received);
	path = get_pwd(env);
	path = ft_strjoin(path, "$ ");
	if (!path)
		path = "$ ";
	else
		path = ft_strchr(path, '/');
	while ((full_cmd = readline(path)) != NULL)
	{
		add_history(full_cmd);
		if (!fill_struct(full_cmd))
		{

			syntax_error(full_cmd);
			if (!s->error)
			{
				check_redirection_syntax();
				if (!s->error)
				{
					invalid_expression(full_cmd);
					get_number_of_tokens(full_cmd);
					detail_cmd();
				}
			}
			// while(s)
			// {
			// 	printf("--- %s",s->cmd);
			// 	s = s->next;
			// }
			// printf("\n");
			ft_lstclear(&s);
		}
		// else
		// 	print_error("syntax error near unexpected tokennnn `|'", 258);
		free(full_cmd);
	}
	signal_received('D');
}
