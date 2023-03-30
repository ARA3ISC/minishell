/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/30 15:24:22 by eej-jama         ###   ########.fr       */
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
	int error;

	error = 0;
	cmd_tmp =ft_strdup(cmd);
	all_cmds = spliting_by_pipe(cmd_tmp);

	if (!all_cmds[0])
		return 0;
	if (check_whitespaces(all_cmds) && all_cmds[1])
	{
		error = print_error("syntax error near unexpected tokenn `|'", 258);
		return error;
	}
	pipes_arr = alloc_pipes(all_cmds);
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		
		ft_lstadd_back(&s, ft_lstnew(all_cmds[i], pipes_arr[i]));
		i++;
	}
	return error;
}

int		help_check_quote(char *string, int *i, int qt)
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

int		checking_quotes(char c, int *i, char *cmd)
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

int	checking_redirection_in_the_last(char *cmd)
{
	int error;

	error = 0;
	int i = ft_strlen(cmd);
	i--;
	while(cmd[i] == ' ')
		i--;
	if(cmd[i] == '>' || cmd[i] == '<')
		error = print_error("syntax error", 258); // 3aaaaaaabi viifie hna l exit status ach khaso ykon !
	return error;
}

void	get_details(t_node *tmp)
{
	// char **tab;

	// tab = ft_strdup(tmp);
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

void	get_var(char *str, char *exp)
{
	int len;
	int i;

	len = 0;
	while (ft_isalnum(str[len]) && str[len])
		len++;


	// printf("len : %d\n", len);
	// exit(1);
	exp = malloc(len + 1);
	if (!exp)
		return ;
	i = 0;
	while (i < len)
	{
		exp[i] = str[i];
		i++;
	}
	exp[i] = '\0';

	printf("var %s\n",exp);
	// exit(0);
}

int var_count(char *cmd)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while(cmd[i])
	{
		if(cmd[i] == 39)
		{
			printf("****\n");
			i++;
			help_check_quote(cmd, &i, 39);
		}
		if(cmd[i] && cmd[i + 1] && cmd[i] == '$' && ft_isalnum(cmd[i + 1]))
			len++;
		i++;
	}
	return len;
}

void alloc_variables(t_node *tmp)
{
	int len;

	len = var_count(tmp->cmd);
	tmp->exp_var = malloc(len * sizeof(char *));
}

void	look_for_dollar(t_node *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// printf("cmd : %s\n", tmp->cmd);

	alloc_variables(tmp);


	while (tmp->cmd[i])
	{
		if(tmp->cmd[i] == 39)
		{
			printf("****\n");
			i++;
			help_check_quote(tmp->cmd, &i, 39);
		}
		if(tmp->cmd[i] && tmp->cmd[i + 1] && tmp->cmd[i] == '$' && ft_isalnum(tmp->cmd[i + 1]))
		{
			get_var(&tmp->cmd[i + 1], tmp->exp_var[j]);
			j++;
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
	int error;

	
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
		error = all_error(full_cmd);
		if(!error)
			error = fill_struct(full_cmd);
		if (!error)
		{
			get_number_of_tokens(full_cmd);
			detail_cmd();
			check_expanding();
			// while(s)
			// {
			// 	printf("cmd  : |%s|\n",s->cmd);
			// 	printf("var  : %s\n",s->exp_var);
			// 	printf("-----\n");
			// 	s = s->next;
			// }
			ft_lstclear(&s);
			free(full_cmd);
		}
	}
	signal_received('D');
}
