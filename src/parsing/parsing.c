/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/12 17:48:43 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_2d_table(char **t)
{
    int    i;

    i = 0;
    while (t[i])
    {
        free(t[i]);
        i++;
    }
    free(t);
}

char	**spliting_by_pipe(char *cmd)
{
	int i = 0;
	char **all_cmds;
	while(cmd[i])
	{
		if(cmd[i] && cmd[i] == '|') // ! fiha mushkil fhad les cas (| dsfdf) (fadfa |) (sddf || dff)
			cmd[i] = '&';
		if(cmd[i] == 39)
		{
			i++;
			while(cmd[i] && cmd[i] != 39)
				i++;
			i++;
		}
		else if(cmd[i] && cmd[i] == 34)
		{
			i++;
			while(cmd[i] && cmd[i] != 34)
				i++;
			i++;
		}
		else
			i++;
	}
	all_cmds = ft_split(cmd, '&');
	return all_cmds;
}

int		fill_struct(char *cmd, t_node **list_cmd)
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
		return print_error("syntax error near unexpected token `|'", 258);
	pipes_arr = alloc_pipes(all_cmds);
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		// if (i == 0)
		// 	ft_lstnew(all_cmds[i], pipes_arr[i]);
		// else
		ft_lstadd_back(list_cmd, ft_lstnew(all_cmds[i], pipes_arr[i]));
		i++;
	}
	// i = 0;
	// while (all_cmds[i])
	// {
	// 	printf("cmd : %s\n", all_cmds[i++]);
	// }
	// list_cmd = &all_cmds;
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
		error = print_error("syntax error", 258);
	return error;
}

int allocate_for_op_and_file(t_node *tmp, int i, int j)
{
	int len;

	len = 0;
	tmp->cmd_dt->op[j] = malloc(sizeof(char) * 3);
	if(!tmp->cmd_dt->op[j])
		exit(1);
		// printf("gggggg\n");
	if(tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
		i++;
	while(tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while(tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t')
	{
		if(tmp->cmd[i] == 34)
		{
			len++;
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 34)
			{
				i++;
				len++;
			}
		}
		if(tmp->cmd[i] == 39)
		{
			len++;
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 39)
			{
				i++;
				len++;
			}
		}
		len++;
		i++;
	}
	// printf("%d\n",len);
	// exit(0);
	tmp->cmd_dt->file[j] = malloc(sizeof(char) * len + 1);
	if(!tmp->cmd_dt->file[j])
		exit(1);
	return len;
}

char *working_in_the_name_of_the_file(char *file_name, int len)
{
	int i = 0;
	int j = 0;
	char *n_name = malloc(len);

	// printf("file : |%s|\n", file_name);
	// exit(0);
		// printf("--> %c\n", file_name[0]);
		// printf("--> %c\n", file_name[1]);
		// printf("--> %c\n", file_name[2]);
		// printf("--> %c\n", file_name[3]);
		// printf("--> %c\n", file_name[4]);
		// exit(10);
	while(file_name[i])
	{
		if(file_name[i] == 34)
		{
			i++;
			while (file_name[i] && file_name[i] != 34)
			{
				n_name[j++] = file_name[i];
				i++;
			}
			i++;
		}
		if(file_name[i] == 39)
		{
			i++;
			while (file_name[i] && file_name[i] != 39)
			{
				n_name[j++] = file_name[i];
				i++;
			}
			i++;
		}
		if(file_name[i] != 34 && file_name[i] != 39)
		{
			n_name[j++] = file_name[i];
			i++;
		}
	}
	n_name[j] = '\0';
	return n_name;
}

void fill_file_name(t_node *tmp, int i, int j)
{
	int k = 0;
	while(tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while(tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t')
	{
		// printf("%c\n",tmp->cmd[i]);
		tmp->cmd_dt->file[j][k++] = tmp->cmd[i];
		if(tmp->cmd[i] == 34)
		{
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 34)
				tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
			tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
		}
		else if(tmp->cmd[i] && tmp->cmd[i] == 39)
		{
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 39)
				tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
			tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
		}
		else
			i++;
	}
	tmp->cmd_dt->file[j][k] = '\0';
	// if(tmp->cmd[i] == 34)
	// {
	// 	while(tmp->cmd[i] && tmp->cmd[i] != 34)
	// 		tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
	// }
	// if(tmp->cmd[i] == 39)
	// {
	// 	while(tmp->cmd[i] && tmp->cmd[i] != 39)
	// 		tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
	// }
	// d = i;
	// while(tmp->cmd[d] && tmp->cmd[d] != '>' && tmp->cmd[d] != '<')
	// 	d++;
	// d--;
	// while(d >= 0 && (tmp->cmd[d] == 32 || tmp->cmd[d] == '\t'))
	// 	d--;
	// while(i <= d)
	// 	tmp->cmd_dt->file[j][k++] = tmp->cmd[i++];
}

// void	fill_file_name(t_node *tmp)
// {
// 	int i = 0;
// 	while (tmp->cmd[i])
// 	{
// 		if (tmp->cmd[i] == '<' || tmp->cmd[i] == '>')
// 		{
// 			if (tmp->cmd[i + 1] && (tmp->cmd[i + 1] == '<' || tmp->cmd[i + 1] == '>'))

// 		}
// 		i++;
// 	}
// }

void	get_details(t_node *tmp)
{
	int i = 0;
	int j = 0;
	int len;
	int k;

	while (tmp->cmd[i])
	{
		if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
		{
			len = allocate_for_op_and_file(tmp, i + 1, j);
			k = 0;
			tmp->cmd_dt->op[j][0] = tmp->cmd[i];
			i++;
			if (tmp->cmd[i] && (tmp->cmd[i] == '<' || tmp->cmd[i] == '>'))
			{
				if (tmp->cmd[i] == '<')
					tmp->cmd_dt->op[j][1] = '<';
				else
					tmp->cmd_dt->op[j][1] = '>';
				tmp->cmd_dt->op[j][2] = '\0';
				i++;
			}
			else
				tmp->cmd_dt->op[j][1] = '\0';
				// printf("uuuuu\n");
			fill_file_name(tmp, i, j);   //! I have problem here !!!!!!!!!!!!!!!!!!!!!!!!!!
			// printf("|%s|\n", tmp->cmd_dt->file[j]);
			// exit(0);

			tmp->cmd_dt->file[j] = working_in_the_name_of_the_file(tmp->cmd_dt->file[j], len);
			// printf("|%s|\n", tmp->cmd_dt->file[j]);
			// exit(0);
			j++;
		}
		i++;
	}
	tmp->cmd_dt->op[j] = NULL;
	tmp->cmd_dt->file[j] = NULL;
}

void	detail_cmd(t_node *list_cmd)
{
	t_node *tmp;

	tmp = list_cmd;
	while (tmp)
	{
		tmp->cmd_dt = malloc(sizeof(t_cmd));
		if(!tmp->cmd_dt)
			return ;
		tmp->cmd_dt->op = malloc(sizeof(char *) * tmp->infos->op_count + 1);
		if(!tmp->cmd_dt->op)
			return ;
		tmp->cmd_dt->file = malloc(sizeof(char *) * tmp->infos->op_count + 1);
		get_details(tmp);


		tmp = tmp->next;
	}
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
	// printf ("len = |%d|\n", len);
	// exit (10);
	tmp->exp_var = malloc((len + 1) * sizeof(char *));
	if(!tmp->exp_var)
		return ;
}

void	get_var(char *str, t_node *tmp, int j)
{
	int len;
	int i;
	char *exp;

	len = 0;
	while (ft_isalnum(str[len]) && str[len])
		len++;

	exp = malloc(len + 1);
	if (!exp)
	{
		printf("lkherr\n");
		return ;
	}
	i = 0;
	while (i < len)
	{
		exp[i] = str[i];
		i++;
	}
	// exp[i] = '\0';

	tmp->exp_var[j] = exp;
	printf("%s\n", tmp->exp_var[j]);
}

void	look_for_dollar(t_node *tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;

	alloc_variables(tmp);

	while (tmp->cmd[i])
	{
		if(tmp->cmd[i] == 39)
		{
			i++;
			help_check_quote(tmp->cmd, &i, 39);
		}
		if(tmp->cmd[i] && tmp->cmd[i + 1] && tmp->cmd[i] == '$' && ft_isalnum(tmp->cmd[i + 1]))
		{
			get_var(&tmp->cmd[i + 1], tmp, j);
			j++;
		}
		i++;
	}
	tmp->exp_var[j] = NULL;
}

void	check_expanding(t_node *list_cmd)
{
	t_node *tmp;

	tmp = list_cmd;
	while (tmp)
	{
		look_for_dollar(tmp);
		tmp = tmp->next;
	}
}

char	*get_eof(char *after_herd)
{
	int i = 0;
	int c = 0;
	int len = 0;
	char *eof;


	while (after_herd[i] == 32 || after_herd[i] == '\t')
		i++;
	if (after_herd[i] == 34)
	{
		i++;
		c = i;
		while (after_herd[i++] != 34)
			len++;
	}

	while (after_herd[i] && after_herd[i] != 32 && after_herd[i++] != 34)
		len++;
	// printf("len : %d\n", len);
	eof = malloc(sizeof(char) * len + 1);
	i = 0;

	while(i <= len && after_herd[c] != 34)
	{
		eof[i++] = after_herd[c];
		c++;
	}
	eof[i] = '\0';

	// printf("eof : %s\n", eof);
	return eof;
}

void	exit_herd(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}

int	start_reading(char *eof)
{
	// (void)eof;
	int fds[2];
	char *rd = NULL;
	char *input = NULL;
	// test = NULL;
	signal(SIGINT, SIG_IGN);
	pipe(fds);
	int id = fork();
	// eof = ft_strtrim(eof, " ");
	if (id == 0)
	{
		signal(SIGINT, &exit_herd);
		while(1)
		{
			rd = readline("herdoc> ");

			if (!ft_strcmp(rd, eof))
			{
				close(fds[1]);
				g_gb.exit_code = print_error(NULL, 1);
				break ;
			}
			input = ft_strjoin2(input, rd);
			input = ft_strjoin( input ,"\n");
			write(fds[1], input, ft_strlen(input) * sizeof(char));
			close(fds[1]);
		}
		// printf("%s", input);
	}
	wait(NULL);
	return fds[0];
}

void	check_herdocs(t_node *list_cmd)
{
	char *eof;
	// char *test = NULL;
	int i;
	int j;

	while (list_cmd)
	{
		i = 0;
		j = 0;
		while (list_cmd->cmd[i])
		{
			if (list_cmd->cmd[i + 1] && list_cmd->cmd[i] == '<' && list_cmd->cmd[i + 1] == '<')
			{
				// printf("****\n");
				// eof = get_eof(&list_cmd->cmd[i + 2]);
				eof = list_cmd->cmd_dt->file[j++];
				list_cmd->inf_fd = start_reading(eof);
			}
			i++;
		}
		list_cmd = list_cmd->next;
	}
}

void	cmd_flags_1st_case(t_node *list_cmd)
{
	char	**split_cmd;
	int len;
	int i;
	if (ft_isalpha(list_cmd->cmd[0]))
	{
		len = 0;
		split_cmd = ft_split(list_cmd->cmd, 32);
		while (split_cmd[len])
			len++;
		list_cmd->cmd_flags = malloc(sizeof(char *) * (len + 1));
		i = 0;
		while (split_cmd[i])
		{
			list_cmd->cmd_flags[i] = split_cmd[i];
			i++;
		}
		list_cmd->cmd_flags[i] = NULL;
	}
}

void	get_cmd_with_flags(t_node *list_cmd)
{

	while (list_cmd)
	{
		cmd_flags_1st_case(list_cmd);
		list_cmd = list_cmd->next;
	}
}

void	fill_my_env(char **env)
{
	int k = 0;
	t_env *tmp;
	char **split_env;
	int len = 0;
	while (env[len])
		len++;

	// 	printf("len %d\n", len);
	// exit(1);
	g_gb.my_env = malloc(sizeof(t_env));
	tmp = g_gb.my_env;
	while (env[k])
	{
		split_env = ft_split(env[k], '=');
		g_gb.my_env->name = malloc(ft_strlen(split_env[0]));
		g_gb.my_env->name = ft_strdup(split_env[0]);
		g_gb.my_env->value = getenv(split_env[0]);

		printf("%s=%s\n", g_gb.my_env->name, g_gb.my_env->value);
		g_gb.my_env->next = malloc(sizeof(t_env));
		g_gb.my_env = g_gb.my_env->next;

		free_2d_table(split_env);
		k++;
	}
	// while (tmp)
	// {
	// 	printf("%s=%s\n", tmp->name, tmp->value);
	// 	tmp = tmp->next;
	// }
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_node *list_cmd = NULL;
	char *path;
	char *full_cmd;
	banner();
	// signal(SIGQUIT, SIG_IGN);


	path = get_pwd(env);
	path = ft_strjoin(path, "$ ");
	if (!path)
		path = "$ ";
	else
		path = ft_strchr(path, '/');
	// g_gb = malloc(sizeof(t_gb));
	// fill_my_env(env);

	while ((full_cmd = readline(path)) != NULL)
	{
		add_history(full_cmd);
		g_gb.exit_code = all_error(full_cmd);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, signal_C_received);

		if(!g_gb.exit_code)
			g_gb.exit_code = fill_struct(full_cmd, &list_cmd);


		if (!g_gb.exit_code)
		{
			get_number_of_tokens(full_cmd, list_cmd);

			detail_cmd(list_cmd);
			check_expanding(list_cmd);
			check_herdocs(list_cmd);

			get_cmd_with_flags(list_cmd);

			if (!ft_strcmp(full_cmd, "env"))
				fill_my_env(env);
			if (!ft_strcmp(full_cmd, "echo $?"))
				printf("%d\n", g_gb.exit_code);

			// while (list_cmd)
			// {
			// 	i = 0;
			// 	while (list_cmd->cmd_flags[i])
			// 	{
			// 		printf("flag %d : %s\n", i, list_cmd->cmd_flags[i]);
			// 		i++;
			// 	}
			// 	printf("-----\n");
			// 	list_cmd = list_cmd->next;
			// }
		}
		// 	int i;
		// while(list_cmd)
		// {
		// 	printf("cmd : %s\n", list_cmd->cmd);
		// 	i = 0;
		// 	while(list_cmd->exp_var[i])
		// 	{
		// 		printf("var  : %s\n",list_cmd->exp_var[i]);
		// 		i++;
		// 	}
		// 	while(list_cmd->cmd_dt->op[i])
		// 	{
		// 		printf("op  : |%s|\n",list_cmd->cmd_dt->op[i]);
		// 		printf("file  : |%s|\n",list_cmd->cmd_dt->file[i]);
		// 		i++;
		// 	}
		// 	printf("-----\n");
		// 	list_cmd = list_cmd->next;
		// }


		// signal(SIGQUIT, SIG_IGN);
		// printf("exit_status : %d\n", g_gb.exit_code);
		signal(SIGQUIT, signal_D_received);
		ft_lstclear(&list_cmd);
		free(full_cmd);
	}
	// printf("hhh\n");
	// signal_received('D');
}
