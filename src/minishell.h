/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:38:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/30 21:25:33 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdarg.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PURPLE "\e[35m"
# define RESET "\n\033[0m"
# define GREEN "\033[0;32m"
# define MINISHELL "minishell-0.1$ "
// # define MINISHELL "\033[0;32mminishell-0.1$ \033[0m"
# define RED "\033[0;31m"

typedef struct s_info
{
	int pipe_count;
	int cmd_count;
}			t_info;

typedef struct s_cmd
{
	// char *cmd;
	char **file;
	char **op;
}			t_cmd;

typedef struct s_node
{
	char *cmd;
	struct s_cmd *cmd_dt;
	int op_count;
	int fds[2];
	char **cmd_flags;
	int inf_fd;
	int outf_fd;
	char **exp_var;
	char *new_cmd;
	int index;
	
	struct s_node *next;
}				t_node;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct s_gb
{
	int exit_code;
	struct s_info *infos;
	int save_infd;
	int save_outfd;
	bool error;
	int pid;
	t_env *my_env;
}				t_gb;

t_gb g_gb;

extern void			rl_replace_line(const char *, int);

t_node				*ft_lstnew(char *_cmd);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_lstclear(t_node **lst);

// ! error
int					print_error(char *msg, int code);
int					check_whitespaces(char **all_cmds);
int					syntax_error(char *cmd);
int					invalid_expression(char *cmd);

void				banner();
int					cmds_count(char **cmds);
char				*get_pwd(char **env);
int					count_op(char *cmd);
void				get_number_of_tokens(char *full_cmd, t_node *list_cmd);
int					count_pipes(char *cmd);

int					**alloc_pipes(char **all_cmds);
void				signal_received(char s);
void				signal_C_received(int signo);
void				signal_D_received(int signo);
int					check_redirection_syntax(char *cmd);
int 				checking_quotes(char c, int *i, char *cmd);
int					checking_redirection_in_the_last(char *cmd);
int					all_error(char *full_cmd);
void				count_herdocs(char *full_cmd);
void				parsing(char **env, t_node *list_cmd);
void 				execution(t_node *list_cmd);
t_env				*ft_lstnew_env(char *name, char *value);
void				ft_lstadd_back_env(t_env **lst, t_env *new);

// ! execution

int					ft_lstsize(t_node *lst);
int					is_builtin(t_node *list_cmd);
void 				execute_list_of_cmds(t_node *list_cmd);
void 				builtins(char *full_cmd);
void 				ft_echo(char *cmd);
void				ft_cd(char *full_cmd);
void 				ft_pwd(char *full_cmd);
void 				ft_exit(char *full_cmd);
void 				ft_export(char *full_cmd);
void 				ft_env(char *full_cmd);
void 				ft_unset(char *cmd);
int 				name_is_exist(char *name);


#endif
