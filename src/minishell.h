/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:38:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/12 17:42:26 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define PURPLE "\e[35m"
# define RESET "\n\033[0m"
# define GREEN "\033[0;32m"
# define MINISHELL "minishell-0.1$ "
# define RED "\033[0;31m"

typedef struct s_info
{
	int				pipe_count;
	int				cmd_count;
}					t_info;

typedef struct s_cmd
{
	char			**file;
	char			**coted;
	char			**eofs;
	char			**op;
	char			**to_open;
}					t_cmd;

typedef struct s_node
{
	char			*cmd;
	struct s_cmd	*cmd_dt;
	int				op_count;
	int				fds[2];
	int				herdocs_count;
	int				var_count;
	char			**cmd_flags;
	int				inf_fd;
	int				outf_fd;
	char			**exp_var;
	char			*new_cmd;
	int				index;
	bool			only_heredoc;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal;
	int				space;
	struct s_env	*next;
}					t_env;

typedef struct s_gb
{
	int				exit_code;
	struct s_info	*infos;
	int				save_infd;
	int				save_outfd;
	char			**env_array;
	int				save_fd;
	bool			error;
	int				pid;
	t_env			*my_env;
	t_env			*my_export;
	int				k;

}					t_gb;
t_gb				g_gb;
extern void			rl_replace_line(const char *s, int i);
t_node				*ft_lstnew(char *_cmd);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_lstclear(t_node **lst);
int					print_error(char *msg, int code);
int					check_whitespaces(char **all_cmds);
int					syntax_error(char *cmd);
int					invalid_expression(char *cmd);
void				banner(void);
int					cmds_count(char **cmds);
int					count_op(char *cmd);
void				get_number_of_tokens(char *full_cmd, t_node *list_cmd);
int					count_pipes(char *cmd);
int					**alloc_pipes(char **all_cmds);
void				signal_c_received(int signo);
int					check_redirection_syntax(char *cmd);
int					checking_quotes(char c, int *i, char *cmd);
int					checking_redirection_in_the_last(char *cmd);
int					all_error(char *full_cmd);
void				count_herdocs(char *full_cmd);
void				parsing(char **env, t_node *list_cmd);
void				execution(t_node *list_cmd);
t_env				*ft_lstnew_env(char *name, char *value, int equal,
						int space);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				ft_putstr_fd(char *str, int fd);
int					ft_atoi(const char *str);
int					ft_lstsize(t_node *lst);
int					is_builtin(t_node *list_cmd);
void				execute_list_of_cmds(t_node *list_cmd);
void				builtins(t_node *full_cmd);
void				ft_echo(t_node *cmd);
void				ft_cd(t_node *full_cmd);
void				ft_pwd(t_node *full_cmd);
void				ft_exit(t_node *full_cmd);
void				ft_export(t_node *full_cmd);
void				ft_env(t_node *full_cmd);
void				ft_unset(t_node *cmd);
int					name_is_exist_in_env(char *name);
int					name_is_exist_in_export(char *name);
char				*get_from_my_env(char *exp, char *quot);
int					open_files(t_node *list_cmd);
int					existe_spaces(char *value);
void				remove_it_exp(char *name);
char				*expend_herdocc(char *input);
void				free_2d_table(char **t);
int					var_count(char *cmd);
int					cmds_count(char **cmds);
void				ft_lstadd_back(t_node **lst, t_node *new);
t_node				*ft_lstnew(char *_cmd);
int					ft_lstsize(t_node *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				free_flags(t_node *lst);
t_env				*ft_lstnew_env(char *name, char *value, int equal,
						int space);
int					fill_struct(char *cmd, t_node **list_cmd);
int					detail_cmd(t_node *list_cmd);
void				fill_my_env(char **env);
void				fill_my_array_env(char **env);
void				skip(char *cmd, int *i, int n);
void				skip2(t_node *tmp, int *i, int *len);
void				fill_op(t_node *tmp, int *i, int *j);
char				*get_var(char *str, t_node *tmp, int j);
void				check_expanding(t_node *list_cmd);
int					allocate_for_op_and_file(t_node *tmp, int i, int j);
int					fill_file_name(t_node *tmp, int i, int j);
char				*working_in_the_name_of_the_file(t_node *cmd, int len,
						int d);
int					help_check_quote(char *string, int *i, int qt);
char				*get_from_my_env(char *exp, char *quot);
void				expanding(t_node *list_cmd);
void				check_herdocs(t_node *list_cmd);
void				exit_herdoc(int signo);
char				*expend_herdocc(char *input);
void				start_reading(t_node *list_cmd, char *eof, char *coted);
void				check_herdocs(t_node *list_cmd);
void				get_cmd_with_flags(t_node *list_cmd);
char				*search_and_replace(char *str, char a, char b);
int					ft_twodim_len(char **p);
void				execute_one_cmd(t_node *list_cmd);
void				check_cmds(t_node *list_cmd);
void				execute_last_cmd(t_node *list_cmd, t_node *tmp);
void				execute_middle_cmds(t_node *list_cmd, t_node *tmp);
void				close_fds(t_node *node, t_node *tm);
void				close_all_fds(t_node *node, t_node *tmp);
int					is_herdoc(t_node *list_cmd);
void				execute_all_cmds(t_node *list_cmd, t_node *tmp, int len);
void				error_case(t_node *list_cmd);
void				ft_putstrfd(char *str, int fd);
void				close_fds(t_node *node, t_node *tmp);
void				close_all_fds(t_node *node, t_node *tmp);
int					var_count(char *cmd);
void				read_from_herdoc(char *eof, char *input, int fd1,
						char *coted);
int					get_len_vars(char *input);
void				cmd_not_found(char *full_cmd);
void				ft_lstdelone_env(t_env *lst);
void				ft_lstclear_env(t_env **lst);
t_env				*ft_lstnew_env(char *name, char *value, int equal,
						int space);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				free_flags(t_node *lst);
void				ft_lstdelone(t_node *lst);
int					skip_d(char *cmd, int i);
int					ft_lstsize(t_node *lst);
void				free_cmd_dt(t_node *lst);
void				free_exp(t_node *lst);
void				ft_lstclear(t_node **lst);
void				free_2d_table(char **t);
void				skipping(char *cmd, int *i);
char				**spliting_by_pipe(char *cmd);
int					error_stx(char **all_cmds);
int					fill_struct(char *cmd, t_node **list_cmd);
int					help_check_quote(char *string, int *i, int qt);
int					checking_quotes(char c, int *i, char *cmd);
int					checking_redirection_in_the_last(char *cmd);
void				skip_p(t_node *tmp, int *i, int *len);
int					get_len_to_alloc(t_node *tmp, int *i, int len);
void				skippo(char *cmd_dt_file_d, int *i, char **n_name, int *j);
char				*get_n_name(char *cmd_dt_file_d, int j, char **n_name);
char				*working_in_the_name_of_the_file(t_node *cmd, int len,
						int d);
void				help_fill_file_name(t_node *tmp, int d, int *k, int *i);
int					fill_file_name(t_node *tmp, int i, int j);
void				fill_opp(t_node *tmp, int *i, int j);
void				fill_file(t_node *tmp, int *i, int *k, int j);
void				skip_and_fill_fname(t_node *tmp, int *i, int *k, int *j);
void				get_details(t_node *tmp);
int					allocate_for_op_and_file(t_node *tmp, int i, int j);
void				skippo(char *cmd_dt_file_d, int *i, char **n_name, int *j);
char				*get_n_name(char *cmd_dt_file_d, int j, char **n_name);
char				*working_in_the_name_of_the_file(t_node *cmd, int len,
						int d);
void				help_fill_file_name(t_node *tmp, int d, int *k, int *i);
int					fill_file_name(t_node *tmp, int i, int j);
void				fill_opp(t_node *tmp, int *i, int j);
void				fill_file(t_node *tmp, int *i, int *k, int j);
void				skip_and_fill_fname(t_node *tmp, int *i, int *k, int *j);
char				*get_eof(char *after_herd);
void				exit_herdoc(int signo);
int					ft_twodim_len(char **p);
char				*search_and_replace(char *str, char a, char b);
int					existe_spaces(char *value);
void				fill_my_env(char **env);
void				look_for_var(t_node *tmp, int j);
char				*expanded_file_name(t_node *cmd, int i);
int					overridee(t_node *list_cmd, char *file, int i);
int					output_redirections(t_node *list_cmd, int i);
int					input_redirections(t_node *list_cmd, int i);
int					open_files(t_node *list_cmd);
void				display_export(t_node *full_cmd);
int					name_is_exist_in_env(char *name);
int					name_is_exist_in_export(char *name);
int					skip_of(char *cmd, int i);
int					get_name_from_double_quot(char *cmd, char **name, int i,
						t_node *full_cmd);
int					get_name_from_simple_quot(char *cmd, char **name, int i,
						t_node *full_cmd);
char				*get_namee(char *cmd, int *i, t_node *full_cmd);
int					ft_is_nbr(char *str);
#endif
