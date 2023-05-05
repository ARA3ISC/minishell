/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/05 06:24:13 by eej-jama         ###   ########.fr       */
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
	all_cmds = spliting_by_pipe(cmd_tmp);
	

	if (!all_cmds[0])
	{
		print_error(NULL, 0);
		return 0;
	}
	if (check_whitespaces(all_cmds) && all_cmds[1])
	{
		print_error("syntax error near unexpected token `|'", 258);
		return 0;
	}
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		ft_lstadd_back(list_cmd, ft_lstnew(all_cmds[i]));
		i++;
	}
	if (all_cmds[0][0] == '\0')
	{
		print_error(NULL, 0);
		return 0;
	}
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
		while(i > 0 && cmd[i] == ' ')
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
	// tmp->cmd_dt->to_open[j] = malloc(2);
	// printf("allocated : %d\n", len);
	if(!tmp->cmd_dt->file[j])
		exit(1);
	// printf("allocated : %d\n", len);
	return len;
}



char	*working_in_the_name_of_the_file(t_node *cmd, int len, int d)
{
	int i = 0;
	int j = 0;

	char *n_name;
	
	cmd->cmd_dt->coted[d] = malloc(2);
	cmd->cmd_dt->coted[d][0] = '0';
	cmd->cmd_dt->coted[d][1] = '\0';
	
	while(cmd->cmd_dt->file[d][i])
	{
		if(cmd->cmd_dt->file[d][i] == '\"' )
			cmd->cmd_dt->coted[d][0] = '1';
		else if(cmd->cmd_dt->file[d][i] == '\'')
			cmd->cmd_dt->coted[d][0] = '2';
			
		i++;
	}
	i = 0;
	n_name = malloc(len + 1);
	while(cmd->cmd_dt->file[d][i])
	{
		if(cmd->cmd_dt->file[d][i] == 34)
		{
			i++;
			while (cmd->cmd_dt->file[d][i] && cmd->cmd_dt->file[d][i] != 34)
			{
				n_name[j++] = cmd->cmd_dt->file[d][i];
				i++;
			}
			i++;
		}
		if(cmd->cmd_dt->file[d][i] && cmd->cmd_dt->file[d][i] == 39)
		{
			i++;
			while (cmd->cmd_dt->file[d][i] && cmd->cmd_dt->file[d][i] != 39)
			{
				n_name[j++] = cmd->cmd_dt->file[d][i];
				i++;
			}
			i++;
		}
		if(cmd->cmd_dt->file[d][i] && cmd->cmd_dt->file[d][i] != 34 && cmd->cmd_dt->file[d][i] != 39)
		{
			n_name[j++] = cmd->cmd_dt->file[d][i];
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
	int k;
	// int d;
	int len;
	int is_eof;

	// printf("cmd : %s\n", tmp->cmd);
	i = 0;
	j = 0;
	k = 0;
	while (tmp->cmd[i])
	{
		// printf("char : |%c|\n", tmp->cmd[i]);
		is_eof = 0;
		if(tmp->cmd[i] == 34)
		{
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 34)
				i++;
			i++;
		}
		else if(tmp->cmd[i] == 39)
		{
			i++;
			while(tmp->cmd[i] && tmp->cmd[i] != 39)
				i++;
			i++;
		}
		else if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
		{
			if (tmp->cmd[i + 1] && tmp->cmd[i] == '<' && tmp->cmd[i + 1] == '<')
				is_eof = 1;
			len = allocate_for_op_and_file(tmp, i + 1, j);
			if (tmp->cmd[i] && tmp->cmd[i] == '<' && tmp->cmd[i + 1] == '>')
			{
				tmp->cmd_dt->op[j][0] = '>';
				tmp->cmd_dt->op[j][1] = '\0';
				tmp->cmd_dt->to_open[j] = ft_strdup("0");
				i = i + 2;
				
			}
			else 
			{
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
				tmp->cmd_dt->to_open[j] = ft_strdup("1");
				
			}
			fill_file_name(tmp, i, j);   //! I have problem here !!!!!!!!!!!!!!!!!!!!!!!!!!
			
			// printf("file : |%s|\n", tmp->cmd_dt->file[j]);
			tmp->cmd_dt->file[j] = working_in_the_name_of_the_file(tmp, len, j);
			// printf("finale file : |%s|\n", tmp->cmd_dt->file[j]);
			if (is_eof)
				tmp->cmd_dt->eofs[k++] = tmp->cmd_dt->file[j];
			j++;
		}
		if (tmp->cmd[i])
			i++;
	}
	tmp->cmd_dt->op[j] = NULL;
	tmp->cmd_dt->file[j] = NULL;
	// printf("k : %d\n", k);
	tmp->cmd_dt->eofs[k] = NULL;

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
	// int i = 0;
	while (list_cmd)
	{
		list_cmd->cmd_dt = malloc(sizeof(t_cmd));
		if(!list_cmd->cmd_dt)
			return 0;
			// printf("count op : %d\n", list_cmd->op_count);
		list_cmd->cmd_dt->op = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		if(!list_cmd->cmd_dt->op)
			return 0;
		// printf("file : %d\n", list_cmd->op_count);
		list_cmd->cmd_dt->file = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		if(!list_cmd->cmd_dt->file)
			return 0;
		list_cmd->cmd_dt->coted = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		if(!list_cmd->cmd_dt->coted)
			return 0;
		list_cmd->cmd_dt->to_open = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		if(!list_cmd->cmd_dt->to_open)
			return 0;
			
		// printf("*** we will allocate %d\n", list_cmd->herdocs_count + 1);
		list_cmd->cmd_dt->eofs = malloc(sizeof(char *) * (list_cmd->herdocs_count + 1));
		// printf
		get_details(list_cmd);
		// i = 0;
		// while(list_cmd->cmd_dt->op[i])
		// {
		// 	// printf("op : %s\n", list_cmd->cmd_dt->op[i]);
		// 	i++;
		// }
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
		if(cmd[i] && cmd[i + 1] && cmd[i] == '$' && ( cmd[i + 1] == '?' || ft_isalnum(cmd[i + 1])))
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
	if(ft_isalnum(str[len]))
		while (ft_isalnum(str[len]) && str[len])
			len++;
	else if(str[len] == '?')
		len++;
	exp = malloc(len + 1);
	if (!exp)
		return NULL;
	i = 0;
	while (i < len)
	{
		exp[i] = str[i];
		i++;
	}
	exp[i] = '\0';
	if(tmp)
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
				if(tmp->cmd[i + 1] && tmp->cmd[i] == '$' && (tmp->cmd[i + 1] == '?' || ft_isalnum(tmp->cmd[i + 1])))
				{
					get_var(&tmp->cmd[i + 1], tmp, j);
					j++;
				}
				i++;
			}
			if(tmp->cmd[i])
				i++;
		}
		if(tmp->cmd[i] && tmp->cmd[i] == '$' && tmp->cmd[i + 1]  && (tmp->cmd[i + 1] == '?' || ft_isalnum(tmp->cmd[i + 1])))
		{
			get_var(&tmp->cmd[i + 1], tmp, j);
			j++;
		}
		if(tmp->cmd[i]) 
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
	
	// exit(0);
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

void    exit_herdoc(int signo)
{
    if (signo == SIGINT)
        exit(1);
}


char * expend_herdocc(char *input)
{
	int i = 0;
	char *result;
	int len = 0;
	char **var ;
	char *new_cmd = NULL;
	int j = 0;

	if(input == NULL)
		return NULL;
	while(input[i])
	{
		if(input[i] == '$' && input[i + 1]  && (input[i + 1] == '?' || ft_isalnum(input[i + 1])))
			len++;
		i++;
	}
	var = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (input[i])
	{
		if(input[i] == '$' && input[i + 1]  && (input[i + 1] == '?' || ft_isalnum(input[i + 1])))
		{
			var[j] = get_var(&input[i + 1], NULL, 0);
			j++;
		}
		i++;
	}
	var[j] = NULL;
	// exit(0);
	// j = 0;
	// while (var[j])
	// {
	// 	printf("var : %s\n", var[j]);
	// 	j++;
	// }
	// exit(0);
	// printf
	i = 0;
	j = 0;
	while (input[i])
	{
		if(input[i] && input[i + 1] && input[i] == '$' && (input[i + 1] == '?' || ft_isalnum(input[i + 1])))
		{
			if(input[i + 1] == '?')
			{
				result = ft_strdup(ft_itoa(g_gb.exit_code));
				i = i + 2;
			}
			else
			{
				result = get_from_my_env(var[j], "5"); 
				// printf("var  ")
				i = i + ft_strlen(var[j]) + 1;
			}
			if (result)
			{
				new_cmd = ft_strjoin2(new_cmd, result);
			}
			else
				new_cmd = ft_strjoin2(new_cmd, "\n");
			
			j++;
			continue;
		}
		else if(input[i])
		{
			new_cmd = ft_strjoin_char(new_cmd, input[i]);
			i++;
		}
	}
	return new_cmd;
}


void    start_reading(t_node *list_cmd, char *eof, char *coted)
{
    int fds[2];
    char *rd = NULL;
    char *input = NULL;
	char *result;
    pipe(fds);
    int id = fork();
    if (id == 0)
    {
		close(fds[0]);
        signal(SIGINT, exit_herdoc);
        while(1)
        {
            rd = readline("herdoc> ");
            if (!rd)
            {
                // printf("**\n");
                exit(0);
            }
            if (!ft_strcmp(rd, eof))
            {
				
				if(coted[0] == '0')
				{
					result = expend_herdocc(input);
                	write(fds[1], result, ft_strlen(result) * sizeof(char));
					// printf("1 : %d\n", fds[1]);
				}
				else
                	write(fds[1], input, ft_strlen(input) * sizeof(char));
                exit(0);
            }
            input = ft_strjoin2(input, rd);
            input = ft_strjoin( input ,"\n");
        }
    }
    else
    {
		// close(fds[0]);
		close(fds[1]);
        list_cmd->inf_fd = fds[0];
		wait(&g_gb.exit_code);
		g_gb.exit_code = WEXITSTATUS(g_gb.exit_code);
		// printf("status : %d\n", g_gb.exit_code);
		// printf("here outf : %d\n", fds[0]);
		// close(fds[0]);
    }
	// printf("fd[0] dyal lpipe : %d\n", fds[0]);
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
				eof = list_cmd->cmd_dt->eofs[j];
				start_reading(list_cmd, eof, list_cmd->cmd_dt->coted[j++]);
			}

			i++;
		}
		// printf("out\n");
		list_cmd = list_cmd->next;
	}

}

void	cmd_flags_1st_case(t_node *list_cmd)
{
	char	*new_cmd = NULL;
	// char	**split_cmd;
	int i = 0;
	while (list_cmd->cmd[i])
	{
				// printf("cat : |%c|\n", list_cmd->cmd[i]);
		
		if(list_cmd->cmd[i] == 34)
		{
			
			i++;
			while(list_cmd->cmd[i] && list_cmd->cmd[i] != 34)
			{
				new_cmd = ft_strjoin_char(new_cmd, list_cmd->cmd[i]);
				i++;
			}
			i++;
		}
		else if(list_cmd->cmd[i] == 39)
		{
			i++;
			while(list_cmd->cmd[i] && list_cmd->cmd[i] != 39)
			{
				new_cmd = ft_strjoin_char(new_cmd, list_cmd->cmd[i]);
				i++;
			}
			i++;
		}
		else if (list_cmd->cmd[i] && (list_cmd->cmd[i] == '>' || list_cmd->cmd[i] == '<'))
		{
			new_cmd = ft_strjoin_char(new_cmd, '&');
			i++;
			if (list_cmd->cmd[i] && (list_cmd->cmd[i] == '>' || list_cmd->cmd[i] == '<'))
				i++;
			while (list_cmd->cmd[i] && list_cmd->cmd[i] == 32)
				i++;
			while (list_cmd->cmd[i] && list_cmd->cmd[i] != 32)
				i++;
		}
		else if(list_cmd->cmd[i] == 32)
		{
			while(list_cmd->cmd[i] && list_cmd->cmd[i] == 32)
				i++;
			new_cmd = ft_strjoin_char(new_cmd, '&');
		}
		else
			new_cmd = ft_strjoin_char(new_cmd, list_cmd->cmd[i++]);
	}
	list_cmd->cmd_flags = ft_split(new_cmd, '&');
	//  i = 0;
	// while(list_cmd->cmd_flags[i])
	// {
	// 	printf("flags : |%s|\n", list_cmd->cmd_flags[i]);
	// 	i++;
	// }
	 
	// printf("new cmd : %s\n", new_cmd);
	// exit(10);
}

void	get_cmd_with_flags(t_node *list_cmd)
{
	while (list_cmd)
	{
		// printf("ddddd\n");
		cmd_flags_1st_case(list_cmd);
		list_cmd = list_cmd->next;
	}

}

int existe_spaces(char *value)
{
	int i = 0;
	if(!value)
		return 0;
	while(value[i])
	{
		if(value[i] == 32)
			return 1;
		i++;
	}	
	return 0;
}

void	fill_my_env(char **env)
{
	int k = 0;
	int i;
	char *name = NULL;
	while (env[k])
	{
		i = 0;
		while (env[k][i] && env[k][i] != '=')
		{
			name = ft_strjoin_char(name, env[k][i]);
			i++;
		}

		ft_lstadd_back_env(&g_gb.my_env, ft_lstnew_env(name, getenv(name), 1, existe_spaces(getenv(name))));
		ft_lstadd_back_env(&g_gb.my_export, ft_lstnew_env(name, getenv(name), 1, existe_spaces(getenv(name))));
		name = NULL;
		k++;
	}
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

char *get_from_my_env(char *exp, char *quot)
{
	
	t_env *tmp;
	tmp = g_gb.my_env;
	
	while(tmp)
	{
		if(!ft_strcmp(exp, tmp->name))
		{
			if(tmp->space && quot[0] == '0')
			{
				printf("minishell: ambiguous redirect\n");
				return "";
			}
			return tmp->value;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void	expanding(t_node *list_cmd)
{
	char *var;
	int i;
	int j = 0;
	// printf("exit code :%d\n", g_gb.exit_code);
	while (list_cmd)
	{
		list_cmd->new_cmd = NULL;
		i = 0;
		
		// printf("cmd : %s\n", list_cmd->cmd);
		while (list_cmd->cmd[i])
		{
			if(list_cmd->cmd[i] == 39)
			{
				i++;
				while(list_cmd->cmd[i] && list_cmd->cmd[i] != 39)
				{
					list_cmd->new_cmd = ft_strjoin_char(list_cmd->new_cmd, list_cmd->cmd[i]);
					i++;
				}
				i++;
			}
			if(list_cmd->cmd[i] == 34)
				i++;
			if(list_cmd->cmd[i] && list_cmd->cmd[i + 1] && list_cmd->cmd[i] == '$' && (list_cmd->cmd[i + 1] == '?' || ft_isalnum(list_cmd->cmd[i + 1])))
			{
				if(list_cmd->cmd[i + 1] == '?')
				{
					var = ft_strdup(ft_itoa(g_gb.exit_code));
					i = i + 2;
				}
				else
				{
					var = get_from_my_env(list_cmd->exp_var[j], "3");
					// printf("var  ")
					i = i + ft_strlen(list_cmd->exp_var[j]) + 1;
				}
				if (var)
				{
					list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, var);
				}
				else
					list_cmd->new_cmd = ft_strjoin2(list_cmd->new_cmd, "\n");
				
				j++;
				continue;
			}
			if(list_cmd->cmd[i])
			{
				list_cmd->new_cmd = ft_strjoin_char(list_cmd->new_cmd, list_cmd->cmd[i]);
				i++;
				
			}
		}
		// if(var)
		// 	free(var);
		// printf("cmd : %s\n", list_cmd->new_cmd);
		g_gb.exit_code = 0;
		list_cmd = list_cmd->next;
	}
}

char	*expanded_file_name(t_node *cmd, int i)
{
	char *r;
	if (cmd->cmd_dt->file[i][1] && cmd->cmd_dt->file[i][0] == '$' && cmd->cmd_dt->coted[i][0] != '2' && (cmd->cmd_dt->file[i][1] == '?' || ft_isalnum(cmd->cmd_dt->file[i][1])))
	{	
		if(cmd->cmd_dt->file[i][1] == '?')
			r = ft_strdup(ft_itoa(g_gb.exit_code));
		else
			r = get_from_my_env(&cmd->cmd_dt->file[i][1], cmd->cmd_dt->coted[i]);
		return r;
	}
	return NULL;
}

int	output_redirections(t_node *list_cmd, int i)
{
	int fd = -2;
	char *file;
	if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">"))
	{
		file = expanded_file_name(list_cmd , i);
		if(file && file[0] == '\0')
			return 0;
		if (file)
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_TRUNC , 0666);
		if(list_cmd->cmd_dt->to_open[i][0] == '1')
			list_cmd->outf_fd = fd;
		// close(fd);
		// printf("%s outfile opened %d\n",list_cmd->cmd_dt->file[i], list_cmd->outf_fd);
	}
	else if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">>"))
	{

		file = expanded_file_name(list_cmd , i);
		if (file)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_APPEND, 0666);
		list_cmd->outf_fd = fd;
	}
	if (fd == -1)
	{
		print_error("minishell: : No such file or directory", 103);
		return 0;
	}
	return 1;
}

int	input_redirections(t_node *list_cmd, int i)
{
	int fd;

	if (!ft_strcmp(list_cmd->cmd_dt->op[i], "<"))
	{
		fd = open(list_cmd->cmd_dt->file[i], O_RDWR);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", list_cmd->cmd_dt->file[i]);
			print_error(NULL, 1);
			return 0;
		}
		list_cmd->inf_fd = fd;
		// close(fd);
		// printf("%s infile opened %d\n",list_cmd->cmd_dt->file[i], list_cmd->inf_fd);
	}
	return 1;
}

int	open_files(t_node *list_cmd)
{
	int i;
	int rd;
	
	rd = 1;
	// while (list_cmd)
	// {
		// printf("cmd : %s\n", list_cmd->cmd);
		i = 0;
		// printf("op : %s\n", list_cmd->cmd_dt->op[0]);
		// printf("to_open : %s\n", list_cmd->cmd_dt->to_open[0]);
		while (list_cmd->cmd_dt->file[i])
		{
			rd = output_redirections(list_cmd, i);
			if(rd)
				rd = input_redirections(list_cmd, i);
			if (!rd)
				break;
			i++;
		}
		// list_cmd = list_cmd->next;
	// }
	
	
	return rd;
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

void	fill_my_array_env(char **env)
{
	int len = 0;
	int i = 0;

	while (env[len])
		len++;
	g_gb.env_array = malloc(sizeof(char *) * (len + 1));


	while (env[i])
	{
		// g_gb.env_array[i] = malloc(ft_strlen(env[i]));
		g_gb.env_array[i] = ft_strdup(env[i]);
		i++;
	}
	g_gb.env_array[i] = NULL;
}

void		parsing(char **env, t_node *list_cmd)
{


	char *path;
	char *full_cmd;
	// int i;

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
	// fill_my_array_env(env);
	signal(SIGINT, signal_C_received);
	while ((full_cmd = readline(MINISHELL)) != NULL)
	{
		// fill_my_export();
		
		// printf("statsus : %d\n", g_gb.exit_code);

		// g_gb.exit_code = 0;
		add_history(full_cmd);
		g_gb.error = all_error(full_cmd);
		
		if(!g_gb.error)
		{

			g_gb.error = fill_struct(full_cmd, &list_cmd);


			// exit(10);
			if (g_gb.error != 0)
			{
				
				get_number_of_tokens(full_cmd, list_cmd);
				g_gb.error = detail_cmd(list_cmd);
	
				
			}
			if (g_gb.error != 0)
			{
					check_expanding(list_cmd);
					expanding(list_cmd);
					// printf("file : |%s|\n", list_cmd->cmd_dt->file[0]);
					// printf("file : |%s|\n", list_cmd->cmd_dt->coted[0]);
					// printf("cmd : |%s|\n", list_cmd->new_cmd);

					check_herdocs(list_cmd);
					
					get_cmd_with_flags(list_cmd);
					execution(list_cmd);
					
				// }
					

				// printf("exit code : %d\n", g_gb.exit_code);
			}
		}
		// else if (g_gb.error != 0)

        		// printf("out : %d\n", list_cmd->outf_fd);
		ft_lstclear(&list_cmd);
		// free(list_cmd);
		list_cmd = NULL;
		signal(SIGQUIT, signal_D_received);
		// free(full_cmd);
		g_gb.error = 0;
	}
}
