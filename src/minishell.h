/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:38:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/03/26 18:16:06 by maneddam         ###   ########.fr       */
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
	struct s_cmd *cmd_dt;
	struct s_info *infos;
	int fds[2];
	struct s_node *next;
	int exit_code;
}				t_node;

t_node *s;

extern void   		 rl_replace_line(const char *, int);

t_node				*ft_lstnew(char *_cmd, int *fds);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_lstclear(t_node **lst);

// ! error
void				print_error(char *msg);
int					check_whitespaces(char **all_cmds);
void				syntax_error(char *cmd);

#endif
// str ">>"
// "$"
// str[0]
//str = "wc -l >> file.txt"
//str = "wc -l $ file.txt"

