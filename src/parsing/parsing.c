/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/04/30 16:59:18 by eej-jama         ###   ########.fr       */
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
		if(cmd[i] && cmd[i] == '|')
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
	return (all_cmds);
}

int		fill_struct(char *cmd, t_node **list_cmd)
{
	int i = 0;
	char **all_cmds;
	char *cmd_tmp = ft_strdup(cmd);
	// int **pipes_arr;

	all_cmds = spliting_by_pipe(cmd_tmp);
	

	if (!all_cmds[0])
	{
		// printf(RED"errir hh\n"RESET);
		print_error(NULL, 0);
		return 0;
	}
	if (check_whitespaces(all_cmds) && all_cmds[1])
	{
		// printf(RED"errir hh\n"RESET);
		print_error("syntax error near unexpected token `|'", 258);
		return 0;
	}
	// while(all_cmds[i])
	// {
	// 	i++;
	// }
	// exit(0);
	// pipes_arr = alloc_pipes(all_cmds);
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		ft_lstadd_back(list_cmd, ft_lstnew(all_cmds[i]));
		i++;
	}
		// ft_lstadd_back(list_cmd, ft_lstnew(NULL));
	// printf("cmd %s\n", (*list_cmd)->cmd);
	// // if((*list_cmd)->next)
	// printf("cmd %s\n", (*list_cmd)->next->cmd);
	// printf("cmd %s\n", (*list_cmd)->next->next->cmd);
	// printf("cmd %s\n", (*list_cmd)->next->next->next->cmd);
	// exit(0);
	return 1;
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
	if (cmd != NULL)
	{
		int i = ft_strlen(cmd);
		if (i != 0)
			i--;
		// printf("i = %d\n", i);
		// exit(0);
		if(cmd[i] == '>' || cmd[i] == '<')
			return (print_error("syntax error", 258));
		while(cmd[i] == ' ')
			i--;
		if(cmd[i] == '>' || cmd[i] == '<')
			return (print_error("syntax error", 258));

	}
	return 0;
}

int allocate_for_op_and_file(t_node *tmp, int i, int j)
{
	int len;

	len = 0;

	if(tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
	{
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 3);
		i++;
	}
	else
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 2);

	while(tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while(tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t'
		&& tmp->cmd[i] != '<' && tmp->cmd[i] != '>')
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
	tmp->cmd_dt->file[j] = malloc(sizeof(char) * len + 1);
	// printf("allocated : %d\n", len);
	if(!tmp->cmd_dt->file[j])
		exit(1);
	// printf("allocated : %d\n", len);
	return len;
}



char	*working_in_the_name_of_the_file(char *file_name, int len)
{
	int i = 0;
	int j = 0;

	char *n_name;

	n_name = malloc(len + 1);
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
	// printf("n_name : %s\n", n_name);
	// exit(0);
	return n_name;
}

void fill_file_name(t_node *tmp, int i, int j)
{
	int k = 0;
	while(tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while(tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t' && tmp->cmd[i] != '<'
		&& tmp->cmd[i] != '>')
	{
		tmp->cmd_dt->file[j][k++] = tmp->cmd[i];
		if(tmp->cmd_dt->file[j][0] == '#')
		{
			print_error("syntax error", 404);
			return;
		}
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
}

void	get_details(t_node *tmp)
{
	int i;
	int j;
	int len;

	// printf("cmd : %s\n", tmp->cmd);
	i = 0;
	j = 0;
	while (tmp->cmd[i])
	{
		if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
		{
			len = allocate_for_op_and_file(tmp, i + 1, j);

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
			fill_file_name(tmp, i, j);   //! I have problem here !!!!!!!!!!!!!!!!!!!!!!!!!!
			tmp->cmd_dt->file[j] = working_in_the_name_of_the_file(tmp->cmd_dt->file[j], len);
			// printf("file |%s|\n", tmp->cmd_dt->file[j]);
			j++;
		}
		if (tmp->cmd[i])
			i++;
	}
	tmp->cmd_dt->op[j] = NULL;
	tmp->cmd_dt->file[j] = NULL;

	// i = 0;
	// while (tmp->cmd_dt->file[i])
	// {
	// 	printf("file |%s|\n", tmp->cmd_dt->file[i]);
	// 	i++;
	// }

	// printf("---\n");
}


int	detail_cmd(t_node *list_cmd)
{
	// int i;
	while (list_cmd)
	{
		list_cmd->cmd_dt = malloc(sizeof(t_cmd));
		if(!list_cmd->cmd_dt)
			return 0;
		list_cmd->cmd_dt->op = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		if(!list_cmd->cmd_dt->op)
			return 0;
		list_cmd->cmd_dt->file = malloc(sizeof(char *) * (list_cmd->op_count + 1));

		get_details(list_cmd);
		if (g_gb.exit_code == 404)
			return 0;
		list_cmd = list_cmd->next;
	}

	return 1;
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
	tmp->exp_var = malloc((len + 1) * sizeof(char *));
	if(!tmp->exp_var)
		return ;
}

char	*get_var(char *str, t_node *tmp, int j)
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
		return NULL;
	}
	i = 0;
	while (i < len)
	{
		exp[i] = str[i];
		i++;
	}
	exp[i] = '\0';

	tmp->exp_var[j] = exp;
	return exp;
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
		if(tmp->cmd[i] == 34)
		{
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 34)
			{
				if(tmp->cmd[i + 1] && tmp->cmd[i] == '$' && ft_isalnum(tmp->cmd[i + 1]))
				{
					get_var(&tmp->cmd[i + 1], tmp, j);
					j++;
				}
				i++;
			}
			i++;
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
	while (list_cmd)
	{
		look_for_dollar(list_cmd);
		list_cmd = list_cmd->next;
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
	eof = malloc(sizeof(char) * len + 1);
	i = 0;
	while(i <= len && after_herd[c] != 34)
	{
		eof[i++] = after_herd[c];
		c++;
	}
	eof[i] = '\0';
	return eof;
}

void	exit_herd(int signo)
{
	if (signo == SIGINT)
	{
		// printf("ped ldakhel %d\n", g_gb.pid);
		// signal(SIGINT, SIG_IGN);
		kill(g_gb.pid, SIGTERM);
	}
}


void	start_reading(t_node *list_cmd, char *eof)
{
	int fds[2];
	char *rd = NULL;
	char *input = NULL;
	pipe(fds);
	int id = fork();
	if (id == 0)
	{
		g_gb.pid = getpid();

		while(1)
		{
			// close(fds[0]);
			rd = readline("herdoc> ");
			if (!ft_strcmp(rd, eof))
			{
				write(fds[1], input, ft_strlen(input) * sizeof(char));
				close(fds[1]);
				g_gb.exit_code = print_error(NULL, 1);
				list_cmd->inf_fd = fds[0];
				exit(0);

			}
			input = ft_strjoin2(input, rd);
			input = ft_strjoin( input ,"\n");
		// printf("%s\n", input);
			
			// close(fds[1]);
		}
	}
	close(fds[0]);
	wait(NULL);
}

void	check_herdocs(t_node *list_cmd)
{
	char *eof;
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
				eof = list_cmd->cmd_dt->file[j++];
				start_reading(list_cmd, eof);
			}
			i++;
		}
		// printf("out\n");
		list_cmd = list_cmd->next;
	}

}

// cmd1 : infile "0" outfile "4"
// cmd2 : infile "5" outfile "6"
// cmd3 : infile "0" outfile "1"

void	cmd_flags_1st_case(t_node *list_cmd)
{
	char	*new_cmd = NULL;
	// char	**split_cmd;
	int i = 0;

	// printf("1 : %c\n", list_cmd->cmd[i]);
	// printf("2 : %c\n", list_cmd->cmd[i + 1]);
	// printf("3 : %c\n", list_cmd->cmd[i + 2]);
	// exit(10);
	while (list_cmd->cmd[i])
	{
		if (list_cmd->cmd[i] == '>' || list_cmd->cmd[i] == '<')
		{
			new_cmd = ft_strjoin_char(new_cmd, ' ');
			i++;
			if (list_cmd->cmd[i] && (list_cmd->cmd[i] == '>' || list_cmd->cmd[i] == '<'))
				i++;
			while (list_cmd->cmd[i] && list_cmd->cmd[i] == 32)
				i++;
			while (list_cmd->cmd[i] && list_cmd->cmd[i] != 32)
				i++;
		}
		else
			new_cmd = ft_strjoin_char(new_cmd, list_cmd->cmd[i]);

		if (list_cmd->cmd[i])
			i++;
	}

	list_cmd->cmd_flags = ft_split(new_cmd, 32);
	// printf("new cmd : %s\n", new_cmd);
	// exit(10);
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
	int i;
	// t_env *tmp;
	// char **split_env;
	char *name = NULL;
	// char *value = NULL;

	// g_gb.my_env = malloc(sizeof(t_env));
	// tmp = g_gb.my_env;
	while (env[k])
	{
		// split_env = ft_split(env[k], '=');
		i = 0;
		while (env[k][i] && env[k][i] != '=')
		{
			// printf("c : %c\n", env[k][i]);
			name = ft_strjoin_char(name, env[k][i]);
			i++;
		}
		// printf("name : %s\n", name);
		// i++;
		// while (env[k][i])
		// {
		// 	value = ft_strjoin_char(value, env[k][i]);
		// 	i++;
		// }
		// tmp->name = malloc(ft_strlen(split_env[0]));
		// tmp->name = ft_strdup(split_env[0]);
		// tmp->value = getenv(split_env[0]);
		// if (env[k])
		// 	tmp->next = malloc(sizeof(t_env));
		// tmp = tmp->next;

		ft_lstadd_back_env(&g_gb.my_env, ft_lstnew_env(name, getenv(name)));

		// free_2d_table(split_env);
		// free(name);
		name = NULL;
		k++;
	}
	// tmp = NULL;
}

void	look_for_var(t_node *tmp, int j)
{
	char *var;

	tmp->new_cmd = malloc(ft_strlen(getenv(tmp->exp_var[j])));

	var = getenv(tmp->exp_var[j]);
	if (var)
		printf("var : %s\n", var);
	else
		printf("Not exist\n");
}

void	expanding(t_node *list_cmd)
{
	char *var;
	int i;
	int j = 0;

	while (list_cmd)
	{
		list_cmd->new_cmd = NULL;
		i = 0;
		while (list_cmd->cmd[i])
		{
			if(list_cmd->cmd[i] && list_cmd->cmd[i + 1] && list_cmd->cmd[i] == '$' && ft_isalnum(list_cmd->cmd[i + 1]))
			{
				var = getenv(list_cmd->exp_var[j]);
				if (var)
					list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, var);
				else
					list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, "\n");
				i = i + ft_strlen(list_cmd->exp_var[j]) + 1;
				j++;
				continue;
			}
			list_cmd->new_cmd = ft_strjoin_char(list_cmd->new_cmd, list_cmd->cmd[i]);
			i++;
		}
		list_cmd = list_cmd->next;
	}
}

char	*expanded_file_name(char *file)
{
	char *r;
	if (file[1] && file[0] == '$' && ft_isalnum(file[1]))
	{
		r = getenv(&file[1]);
		return r;
	}
	return NULL;
}

void	output_redirections(t_node *list_cmd, int i)
{
	int fd = -2;
	char *file;
	if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">"))
	{
		file = expanded_file_name(list_cmd->cmd_dt->file[i]);
		if (file)
			fd = open(file, O_CREAT | O_RDWR, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR, 0666);
		list_cmd->outf_fd = fd;
		// printf("%s outfile opened %d\n",list_cmd->cmd_dt->file[i], list_cmd->outf_fd);
	}
	else if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">>"))
	{
		file = expanded_file_name(list_cmd->cmd_dt->file[i]);
		if (file)
			fd = open(file, O_CREAT | O_RDWR, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
		list_cmd->outf_fd = fd;
		// printf("%s outfile opened %d\n",list_cmd->cmd_dt->file[i], list_cmd->outf_fd);
	}
	if (fd == -1)
		print_error("Error opening file\n", 103);
}

void	input_redirections(t_node *list_cmd, int i)
{
	int fd;

	if (!ft_strcmp(list_cmd->cmd_dt->op[i], "<"))
	{
		fd = open(list_cmd->cmd_dt->file[i], O_RDWR);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", list_cmd->cmd_dt->file[i]);
			print_error(NULL, 1);
		}
		list_cmd->inf_fd = fd;
		// printf("%s infile opened %d\n",list_cmd->cmd_dt->file[i], list_cmd->inf_fd);
	}
}

int	open_files(t_node *list_cmd)
{
	int i;

		// printf("%s\n");
		// exit(0);
	while (list_cmd)
	{
		i = 0;
		while (list_cmd->cmd_dt->file[i])
		{
			output_redirections(list_cmd, i);
			input_redirections(list_cmd, i);
			i++;
		}
		// printf("infile : %d\noutfile : %d\n", list_cmd->inf_fd, list_cmd->outf_fd);
		list_cmd = list_cmd->next;
	}
	return 0;
}

void	count_herdocs(char *full_cmd)
{
	int i = 0;
	int count = 0;

	while (full_cmd[i])
	{
		if (full_cmd[i + 1] && full_cmd[i] == '<' && full_cmd[i + 1] == '<')
			count++;
		i++;
	}

	if (count > 16)
		exit(print_error("maximum here-document count exceeded", 2));
}

void	print_list(t_node *list_cmd)
{
	int i;
	while (list_cmd)
	{
		i = 0;
		while (list_cmd->cmd_dt->file[i])
		{
			// printf("file [%d] : %s\n", i, list_cmd->cmd_dt->file[i]);
			i++;
		}
		list_cmd = list_cmd->next;
	}
}

void		parsing(char **env, t_node *list_cmd)
{


	char *path;
	char *full_cmd;

	banner();
	// signal(SIGINT, SIG_IGN);


	// signal(SIGQUIT, signal_D_received);
	path = get_pwd(env);
	path = ft_strjoin(path, "$ ");
	if (!path)
		path = "$ ";
	else
		path = ft_strchr(path, '/');
	fill_my_env(env);
	signal(SIGINT, signal_C_received);
	while ((full_cmd = readline(MINISHELL)) != NULL)
	{

		add_history(full_cmd);
		g_gb.error = all_error(full_cmd);
		if(!g_gb.error)
		{
			
			g_gb.error = fill_struct(full_cmd, &list_cmd);
			// while(list_cmd)
			// {
			// 	printf("cmds %s\n", (list_cmd)->cmd);
			// 	(list_cmd) = (list_cmd)->next;
			// }

			// exit(10);
			if (g_gb.error != 0)
			{
				get_number_of_tokens(full_cmd, list_cmd);
				
				g_gb.error = detail_cmd(list_cmd);
			}
			if (g_gb.error != 0)
			{
				if (!ft_strcmp(full_cmd, "$?"))
					printf("exit code :%d\n", g_gb.exit_code);
				open_files(list_cmd);
				check_expanding(list_cmd);
				check_herdocs(list_cmd);
				expanding(list_cmd);
				get_cmd_with_flags(list_cmd);
				
				// builtins(list_cmd->new_cmd);
				execution(list_cmd);
			}
		}
		else if (g_gb.error != 0)
			g_gb.exit_code = 0;

		ft_lstclear(&list_cmd);
		// free(list_cmd);
		// list_cmd = NULL;
		signal(SIGQUIT, signal_D_received);
		free(full_cmd);
		g_gb.error = 0;
	}

	// signal_received('D');

}