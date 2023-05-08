/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:16:26 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/08 02:31:45 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	free_2d_table(char **t)
{
	int	i;

	if (!t)
		return ;
	i = 0;
	// exit(0);
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	skipping(char *cmd, int *i)
{
	if (cmd[*i] == 39)
		{
			(*i)++;
			while (cmd[*i] && cmd[*i] != 39)
				(*i)++;
			(*i)++;
		}
		else if (cmd[*i] && cmd[*i] == 34)
		{
			(*i)++;
			while (cmd[*i] && cmd[*i] != 34)
				(*i)++;
			(*i)++;
		}
		else
			(*i)++;
}

char	**spliting_by_pipe(char *cmd)
{
	int		i;
	char	**all_cmds;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '|')
			cmd[i] = '&';
		skipping(cmd, &i);
	}
	all_cmds = ft_split(cmd, '&');
	return (all_cmds);
}

int	error_stx(char	**all_cmds)
{
	if (!all_cmds[0])
	{
		free(all_cmds);
		print_error(NULL, 0);
		return (0);
	}
	if (check_whitespaces(all_cmds) && all_cmds[1])
	{
		free(all_cmds);
		print_error("syntax error near unexpected token `|'", 258);
		return (0);
	}
	return 1;
}

int	fill_struct(char *cmd, t_node **list_cmd)
{
	int		i;
	char	**all_cmds;
	char	*cmd_tmp;

	i = 0;
	cmd_tmp = ft_strdup(cmd);
	all_cmds = spliting_by_pipe(cmd_tmp);
	free(cmd_tmp);
	if (!error_stx(all_cmds))
		return 0;
	while (all_cmds[i])
	{
		all_cmds[i] = ft_strtrim(all_cmds[i], " ");
		all_cmds[i] = ft_strtrim(all_cmds[i], "\t");
		ft_lstadd_back(list_cmd, ft_lstnew(all_cmds[i]));
		i++;
	}
	free(all_cmds);
	return (1);
}

int	help_check_quote(char *string, int *i, int qt)
{
	int	check;

	check = 1;
	while (string[*i])
	{
		if (string[*i] == qt)
		{
			check = 0;
			break ;
		}
		(*i)++;
	}
	return (check);
}

int	checking_quotes(char c, int *i, char *cmd)
{
	int	check;
	int	qt;

	check = 0;
	if (c == 39)
	{
		(*i)++;
		qt = 39;
		check = help_check_quote(cmd, i, qt);
	}
	if (c == 34)
	{
		(*i)++;
		qt = 34;
		check = help_check_quote(cmd, i, qt);
	}
	return (check);
}

int	checking_redirection_in_the_last(char *cmd)
{
	int	i;

	if (cmd != NULL)
	{
		i = ft_strlen(cmd);
		if (i != 0)
			i--;
		while (i > 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
			i--;
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			print_error("Syntax error", 258);
			return (1);
		}
	}
	return (0);
}

void	skip_p(t_node *tmp, int *i, int *len)
{
	if (tmp->cmd[*i] == 34)
	{
		(*len)++;
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
		{
			(*i)++;
			(*len)++;
		}
	}
	if (tmp->cmd[*i] == 39)
	{
		(*len)++;
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
		{
			(*i)++;
			(*len)++;
		}
	}
}

int get_len_to_alloc(t_node *tmp, int *i, int len)
{
	while (tmp->cmd[*i] && tmp->cmd[*i] != 32 && tmp->cmd[*i] != '\t'
		&& tmp->cmd[*i] != '<' && tmp->cmd[*i] != '>')
	{
		skip_p(tmp, i, &len);
		len++;
		(*i)++;
	}
	return len;
}

int	allocate_for_op_and_file(t_node *tmp, int i, int j)
{
	int	len;

	len = 0;
	if (tmp->cmd[i] == '>' || tmp->cmd[i] == '<')
	{
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 3);
		i++;
	}
	else
		tmp->cmd_dt->op[j] = malloc(sizeof(char) * 2);
	while (tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	len = get_len_to_alloc(tmp, &i, len);
	// printf("len : %d\n", len);

	tmp->cmd_dt->file[j] = malloc(sizeof(char) * len + 1);
	if (!tmp->cmd_dt->file[j])
		exit(1);
	return (len);
}

void	skippo(char *cmd_dt_file_d, int *i, char **n_name, int *j)
{
	if (cmd_dt_file_d[*i] == 34)
	{
		(*i)++;
		while (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] != 34)
		{
			(*n_name)[(*j)++] = cmd_dt_file_d[*i];
			(*i)++;
		}
		(*i)++;
	}
	if (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] == 39)
	{
		(*i)++;
		while (cmd_dt_file_d[*i] && cmd_dt_file_d[*i] != 39)
		{
			(*n_name)[(*j)++] = cmd_dt_file_d[*i];
			(*i)++;
		}
		(*i)++;
	}
}

char	*get_n_name(char *cmd_dt_file_d, int j, char **n_name)
{
	int i;

	i = 0;
	while (cmd_dt_file_d[i])
	{
		skippo(cmd_dt_file_d, &i, n_name, &j);
		if (cmd_dt_file_d[i] && cmd_dt_file_d[i] != 34
			&& cmd_dt_file_d[i] != 39)
		{
			(*n_name)[j++] = cmd_dt_file_d[i];
			i++;
		}
	}
	(*n_name)[j] = '\0';
	return *n_name;
}

char	*working_in_the_name_of_the_file(t_node *cmd, int len, int d)
{
	int		i;
	int		j;
	char	*n_name;

	i = 0;
	j = 0;
	while (cmd->cmd_dt->file[d][i])
	{
		if (cmd->cmd_dt->file[d][i] == '\"')
			cmd->cmd_dt->coted[d][0] = '1';
		else if (cmd->cmd_dt->file[d][i] == '\'')
			cmd->cmd_dt->coted[d][0] = '2';
		i++;
	}
	i = 0;
	n_name = malloc(len + 1);
	n_name = get_n_name(cmd->cmd_dt->file[d], j, &n_name);
	free(cmd->cmd_dt->file[d]);
	return (n_name);
}

void	help_fill_file_name(t_node *tmp, int d, int *k, int *i)
{
	if (tmp->cmd[*i] == 34)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
			tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		printf("kk > |%d|\n", *k);
	}
	else if (tmp->cmd[*i] && tmp->cmd[*i] == 39)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
			tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
		tmp->cmd_dt->file[d][(*k)++] = tmp->cmd[(*i)++];
	}
	else
		(*i)++;
}

int	fill_file_name(t_node *tmp, int i, int j)
{
	int	k;

	k = 0;
	while (tmp->cmd[i] && (tmp->cmd[i] == 32 || tmp->cmd[i] == '\t'))
		i++;
	while (tmp->cmd[i] && tmp->cmd[i] != 32 && tmp->cmd[i] != '\t'
		&& tmp->cmd[i] != '<' && tmp->cmd[i] != '>')
	{
		tmp->cmd_dt->file[j][k++] = tmp->cmd[i];
		if (tmp->cmd_dt->file[j][0] == '#')
		{
			print_error("syntax error", 404);
			return (1);
		}
		help_fill_file_name(tmp, j, &k, &i);
	}
	tmp->cmd_dt->file[j][k] = '\0';
	return (0);
}

void	fill_opp(t_node *tmp, int *i, int j)
{
	tmp->cmd_dt->op[j][0] = tmp->cmd[*i];
	(*i)++;
	if (tmp->cmd[*i] && (tmp->cmd[*i] == '<' || tmp->cmd[*i] == '>'))
	{
		if (tmp->cmd[*i] == '<')
			tmp->cmd_dt->op[j][1] = '<';
		else
			tmp->cmd_dt->op[j][1] = '>';
		tmp->cmd_dt->op[j][2] = '\0';
		(*i)++;
	}
	else
		tmp->cmd_dt->op[j][1] = '\0';
	tmp->cmd_dt->to_open[j] = ft_strdup("1");
}

void	fill_file(t_node *tmp, int *i, int *k, int j)
{
	int is_eof = 0;
	int len;

	if (tmp->cmd[*i + 1] && tmp->cmd[*i] == '<' && tmp->cmd[*i + 1] == '<')
		is_eof = 1;
	len = allocate_for_op_and_file(tmp, *i + 1, j);
	if (tmp->cmd[*i] && tmp->cmd[*i] == '<' && tmp->cmd[*i + 1] == '>')
	{
		tmp->cmd_dt->op[j][0] = '>';
		tmp->cmd_dt->op[j][1] = '\0';
		tmp->cmd_dt->to_open[j] = ft_strdup("0");
		*i = *i + 2;
	}
	else
	{
		fill_opp(tmp, i, j);
	}
	g_gb.error = fill_file_name(tmp, *i, j);
	tmp->cmd_dt->coted[j] = ft_strdup("0");
	if (g_gb.error)
		return ;
	tmp->cmd_dt->file[j] = working_in_the_name_of_the_file(tmp, len, j);
	if (is_eof)
		tmp->cmd_dt->eofs[(*k)++] = ft_strdup(tmp->cmd_dt->file[j]);
}

void	skip_and_fill_fname(t_node *tmp, int *i, int *k, int *j)
{
	if (tmp->cmd[*i] == 34)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 34)
			(*i)++;
		(*i)++;
	}
	else if (tmp->cmd[*i] == 39)
	{
		(*i)++;
		while (tmp->cmd[*i] && tmp->cmd[*i] != 39)
			(*i)++;
		(*i)++;
	}
	else if (tmp->cmd[*i] == '>' || tmp->cmd[*i] == '<')
	{
		fill_file(tmp, i, k, *j);
		(*j)++;
	}
	else
		(*i)++;
}

void	get_details(t_node *tmp)
{
	int	i;
	int	j;
	int	k;
	int	is_eof;

	i = 0;
	j = 0;
	k = 0;
	while (tmp->cmd[i])
	{
		is_eof = 0;
		skip_and_fill_fname(tmp, &i, &k, &j);
	}
	tmp->cmd_dt->op[j] = NULL;
	tmp->cmd_dt->file[j] = NULL;
	tmp->cmd_dt->to_open[j] = NULL;
	tmp->cmd_dt->coted[j] = NULL;
	tmp->cmd_dt->eofs[k] = NULL;
}

int	detail_cmd(t_node *list_cmd)
{
	while (list_cmd)
	{
		list_cmd->cmd_dt = malloc(sizeof(t_cmd));
		list_cmd->cmd_dt->op = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		list_cmd->cmd_dt->file = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		list_cmd->cmd_dt->coted = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		list_cmd->cmd_dt->to_open = malloc(sizeof(char *) * (list_cmd->op_count + 1));
		list_cmd->cmd_dt->eofs = malloc(sizeof(char *) * (list_cmd->herdocs_count + 1));
		get_details(list_cmd);
		if (g_gb.exit_code == 404)
			return 0;
		list_cmd = list_cmd->next;
	}
	return 1;
}



char	*get_eof(char *after_herd)
{
	int		i;
	int		c;
	int		len;
	char	*eof;

	i = 0;
	c = 0;
	len = 0;
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
	while (i <= len && after_herd[c] != 34)
		eof[i++] = after_herd[c++];
	eof[i] = '\0';
	return eof;
}

void	exit_herdoc(int signo)
{
	if (signo == SIGINT)
		exit(1);
}

int	ft_twodim_len(char **p)
{
	int	i;

	i = 0;
	if (!p || !p[i])
		return (0);
	while (p[i])
		i++;
	return (i);
}

char	*search_and_replace(char *str, char a, char b)
{
	int	i;

	i = 0;
	if (!str)
		return NULL;
	while (str[i])
	{
		if (str[i] == a)
			str[i] = b;
		i++;
	}
	return str;
}



int	existe_spaces(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return 0;
	while (value[i])
	{
		if (value[i] == 32)
			return 1;
		i++;
	}
	return 0;
}

void	fill_my_env(char **env)
{
	int		k;
	int		i;
	char	*name;

	k = 0;
	name = NULL;
	while (env[k])
	{
		i = 0;
		while (env[k][i] && env[k][i] != '=')
		{
			name = ft_strjoin_char(name, env[k][i]);
			i++;
		}
		ft_lstadd_back_env(&g_gb.my_env, ft_lstnew_env(name, getenv(name), 1,
					existe_spaces(getenv(name))));
		ft_lstadd_back_env(&g_gb.my_export, ft_lstnew_env(name, getenv(name), 1,
					existe_spaces(getenv(name))));
		// free(name);
		name = NULL;
		k++;
	}
}

void	look_for_var(t_node *tmp, int j)
{
	char	*var;

	tmp->new_cmd = malloc(ft_strlen(getenv(tmp->exp_var[j])));
	var = getenv(tmp->exp_var[j]);
	if (var)
		printf("var : %s\n", var);
	else
		printf("Not exist\n");
}

char	*expanded_file_name(t_node *cmd, int i)
{
	char	*r;

	if (cmd->cmd_dt->file[i][1] && cmd->cmd_dt->file[i][0] == '$'
		&& cmd->cmd_dt->coted[i][0] != '2' && (cmd->cmd_dt->file[i][1] == '?'
			|| ft_isalnum(cmd->cmd_dt->file[i][1])))
	{
		if (cmd->cmd_dt->file[i][1] == '?')
			r = ft_strdup(ft_itoa(g_gb.exit_code));
		else
			r = get_from_my_env(&cmd->cmd_dt->file[i][1],
					cmd->cmd_dt->coted[i]);
		return r;
	}
	return NULL;
}

int	overridee(t_node *list_cmd, char *file, int i)
{
	int fd;

	fd = 0;
	file = expanded_file_name(list_cmd, i);
	if (file && file[0] == '\0')
		return 0;
	if (file)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else
		fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_TRUNC,
				0666);
	if (list_cmd->cmd_dt->to_open[i][0] == '1')
		list_cmd->outf_fd = fd;
	return fd;
}

int	output_redirections(t_node *list_cmd, int i)
{
	int		fd;
	char	*file;

	fd = -2;
	file = NULL;
	if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">"))
		overridee(list_cmd, file, i);
	else if (!ft_strcmp(list_cmd->cmd_dt->op[i], ">>"))
	{
		file = expanded_file_name(list_cmd, i);
		if (file)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			fd = open(list_cmd->cmd_dt->file[i], O_CREAT | O_RDWR | O_APPEND,
					0666);
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
	int	fd;

	if (!ft_strcmp(list_cmd->cmd_dt->op[i], "<"))
	{
		fd = open(list_cmd->cmd_dt->file[i], O_RDWR);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n",
					list_cmd->cmd_dt->file[i]);
			print_error(NULL, 1);
			return 0;
		}
		list_cmd->inf_fd = fd;
	}
	return 1;
}

int	open_files(t_node *list_cmd)
{
	int	i;
	int	rd;

	rd = 1;
	i = 0;
	while (list_cmd->cmd_dt->file[i])
	{
		rd = output_redirections(list_cmd, i);
		if (rd)
			rd = input_redirections(list_cmd, i);
		if (!rd)
			break ;
		i++;
	}
	return rd;
}

void	count_herdocs(char *full_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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
	int	i;

	while (list_cmd)
	{
		i = 0;
		while (list_cmd->cmd_dt->file[i])
			i++;
		list_cmd = list_cmd->next;
	}
}

void	fill_my_array_env(char **env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	g_gb.env_array = malloc(sizeof(char *) * (len + 1));
	while (env[i])
	{
		g_gb.env_array[i] = ft_strdup(env[i]);
		i++;
	}
	g_gb.env_array[i] = NULL;
}

void	begin_manipulation(char *full_cmd, t_node **list_cmd)
{
		g_gb.error = fill_struct(full_cmd, list_cmd);
		if (g_gb.error != 0)
		{
			get_number_of_tokens(full_cmd, *list_cmd);
			g_gb.error = detail_cmd(*list_cmd);
			if (g_gb.error != 0)
			{
				check_expanding(*list_cmd);
				expanding(*list_cmd);
				check_herdocs(*list_cmd);
				get_cmd_with_flags(*list_cmd);
				execution(*list_cmd);
			}
			free(g_gb.infos);
			ft_lstclear(list_cmd);
		}
}

void	parsing(char **env, t_node *list_cmd)
{
	char	*full_cmd;

	banner();
	signal(SIGINT, SIG_IGN);
	fill_my_env(env);
	fill_my_array_env(env);
	signal(SIGINT, signal_c_received);
	signal(SIGQUIT, SIG_IGN);
	while ((full_cmd = readline(MINISHELL)) != NULL)
	{
		add_history(full_cmd);
		g_gb.error = all_error(full_cmd);
		if (!g_gb.error)
			begin_manipulation(full_cmd, &list_cmd);
		free(full_cmd);
		list_cmd = NULL;
		g_gb.error = 0;
	}
	// system("leaks minishell");
	printf("exit\n");
	exit(g_gb.exit_code);
}
