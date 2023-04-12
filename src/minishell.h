/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:38:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/11 15:47:40 by maneddam         ###   ########.fr       */
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
# define RED "\033[0;31m"

typedef struct s_info
{
	int op_count;
	int pipe_count;
	int cmd_count;
}			t_info;

typedef struct s_cmd
{
	char *cmd;
	char **file;
	char **op;
}			t_cmd;

typedef struct s_node
{
	char *cmd;
	struct s_info *infos;
	struct s_cmd *cmd_dt;
	int inf_fd;
	int outf_fd;
	struct s_node *next;
	char **exp_var;
}				t_node;

int exit_code;

extern void			rl_replace_line(const char *, int);

t_node				*ft_lstnew(char *_cmd, int *fds);
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
int					check_redirection_syntax(char *cmd);
int 				checking_quotes(char c, int *i, char *cmd);
int					checking_redirection_in_the_last(char *cmd);
int					all_error(char *full_cmd);
#endif

