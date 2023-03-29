/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/29 22:10:40 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**spliting_by_pipe(char *cmd)
{
	int i = 0;
	char **all_cmds;
	while(cmd[i])
	{
		if(cmd[i] == 39)
		{
			i++;
			while(cmd[i] != 39)
				i++;
			i++;
		}
		if(cmd[i] && cmd[i] == 34)
		{
			i++;
			while(cmd[i] != 34)
				i++;
			i++;
		}
		if(cmd[i] && cmd[i] == '|') // ! fiha mushkil fhad les cas (| dsfdf) (fadfa |) (sddf || dff)
			cmd[i] = '&';
		i++;
	}
	all_cmds = ft_split(cmd, '&');
	return all_cmds;
}

int		fill_struct(char *cmd)
{
	int i = 0;
	char **all_cmds;
	int **pipes_arr;
	char *cmd_tmp;

	cmd_tmp =ft_strdup(cmd);
	all_cmds = spliting_by_pipe(cmd_tmp);

	if (!all_cmds[0])
		return 0;
	if (check_whitespaces(all_cmds))
	{
		print_error("syntax error near unexpected token `|'", 258);
		//! hna khass n nssetiw exit code l 0 ms rh lvariable li f struct baqi mamallocyinsh lih so tatsegfaulty
		return 0;
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
	return 1;
}

int		help_check_quote(char *string, size_t *i, int qt)
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

int		checking_quotes(char c, size_t *i, char *cmd)
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

void	checking_redirection_in_the_last(char *cmd)
{
	size_t i = ft_strlen(cmd);
	i--;
	while(cmd[i] == ' ')
		i--;
	if(cmd[i] == '>' || cmd[i] == '<')
		print_error("syntax error", 258); // 3aaaaaaabi viifie hna l exit status ach khaso ykon !
}

void	get_details(t_node *tmp)
{
	// char **tab;

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
			tmp->cmd[i] = '&';
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
	// tab = ft_split(tmp->cmd, '&');
	tmp->cmd_dt->cmd = tmp->cmd;
	// printf("%s\n",tmp->cmd_dt->cmd);

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

void	get_var(char *str, t_node *tmp)
{
	int len;
	int i;

	len = 0;
	while (ft_isalnum(str[len]) && str[len])
		len++;


	// printf("len : %d\n", len);
	// exit(1);
	tmp->exp_var = malloc(len + 1);
	if (!tmp->exp_var)
		return ;
	i = 0;
	while (i < len)
	{
		tmp->exp_var[i] = str[i];
		i++;
	}
	tmp->exp_var[i] = '\0';

	// printf("var %s\n", s->exp_var);
	// exit(0);
}

void	look_for_dollar(t_node *tmp)
{
	size_t i;
	int len;

	i = 0;
	len = 0;
	// printf("cmd : %s\n", tmp->cmd);

	// alloc_variables(tmp);


	while (tmp->cmd[i])
	{
		if(tmp->cmd[i] == 39)
		{
			printf("****\n");
			i++;
			help_check_quote(tmp->cmd, &i, 39);
		}
		if(tmp->cmd[i] && tmp->cmd[i + 1] && tmp->cmd[i] == '$')
		{
			get_var(&tmp->cmd[i + 1], tmp);
		}
		i++;
	}
}

void	check_expanding()
{
	t_node *tmp;

	tmp = s;
	while (tmp)
	{
		look_for_dollar(tmp);
		// printf("cmd : %s\n", tmp->cmd); //
		tmp = tmp->next;
	}

}

int		main(int argc, char **argv, char **env)
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
		get_number_of_tokens(full_cmd);
		invalid_expression(full_cmd);
		syntax_error(full_cmd);
		if (fill_struct(full_cmd))
		{
			if (!s->error)
			{
				check_redirection_syntax();
				if (!s->error)
				{
					detail_cmd();
					check_expanding();
					while(s)
					{
						printf("cmd  : %s\n",s->cmd);
						printf("var  : %s\n",s->exp_var);
						printf("-----\n");
						s = s->next;
					}
				}
			}

			ft_lstclear(&s);
			free(full_cmd);
		}
		// else
		// 	print_error("syntax error near unexpected tokennnn `|'", 258);
	}
	signal_received('D');
}
