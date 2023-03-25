/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:38:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/03/25 15:12:23 by eej-jama         ###   ########.fr       */
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

typedef struct s_node
{
	char *cmd;
	int *fds;
	struct s_node *next;
}				t_node;

t_node *cmd_struct;

void				print_error(char *msg);

t_node				*ft_lstnew(char *_cmd, int *fds);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_lstclear(t_node **lst);
extern void    rl_replace_line(const char *, int);

#endif
