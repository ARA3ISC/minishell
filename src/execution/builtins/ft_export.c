/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:33:14 by eej-jama          #+#    #+#             */
/*   Updated: 2023/05/07 19:32:26 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_export(t_node *full_cmd)
{
	t_env	*tmp;

	tmp = g_gb.my_export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", full_cmd->outf_fd);
		ft_putstr_fd(tmp->name, full_cmd->outf_fd);
		if (tmp->equal)
		{
			ft_putstr_fd("=\"", full_cmd->outf_fd);
			if (tmp->value)
				ft_putstr_fd(tmp->value, full_cmd->outf_fd);
			ft_putstr_fd("\"\n", full_cmd->outf_fd);
		}
		else
			ft_putstr_fd("\n", full_cmd->outf_fd);
		tmp = tmp->next;
	}
}

int	name_is_exist_in_env(char *name)
{
	t_env	*tmp;

	tmp = g_gb.my_env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	name_is_exist_in_export(char *name)
{
	t_env	*tmp;

	tmp = g_gb.my_export;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	skip_of(char *cmd, int i)
{
	i++;
	if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		i++;
	while (cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
		i++;
	if (cmd[i] && cmd[i] == 34)
	{
		i++;
		while (cmd[i] && cmd[i] != 34)
			i++;
		i++;
	}
	else if (cmd[i] && cmd[i] == 39)
	{
		i++;
		while (cmd[i] && cmd[i] != 39)
			i++;
		i++;
	}
	else
		while (cmd[i] && cmd[i] != 32 && cmd[i] != '\t')
			i++;
	return (i);
}

int	get_name_from_double_quot(char *cmd, char **name, int i, t_node *full_cmd)
{
	i++;
	while (cmd[i] && cmd[i] != 34)
	{
		if ((cmd[i] < 65 && cmd[i] > 31) || cmd[i] == '\0')
		{
			ft_putstr_fd("minishell: export: not a valid identifier",
				full_cmd->outf_fd);
			ft_putstr_fd("\n", full_cmd->outf_fd);
			return (0);
		}
		*name = ft_strjoin_char(*name, cmd[i++]);
	}
	i++;
	return (i);
}

int	get_name_from_simple_quot(char *cmd, char **name, int i, t_node *full_cmd)
{
	i++;
	while (cmd[i] && cmd[i] != 39)
	{
		if ((cmd[i] < 65 && cmd[i] > 31 ) || cmd[i] == '\0')
		{
			ft_putstr_fd("minishell: export: not a valid identifier", full_cmd->outf_fd);
			ft_putstr_fd("\n", full_cmd->outf_fd);
			return 0; 
		}
		*name = ft_strjoin_char(*name, cmd[i++]);
	}
	i++;
	return i;
}

char *get_namee(char *cmd, int *i, t_node *full_cmd)
{
	char *name;

	name = NULL; 
	while(cmd[*i] && cmd[*i] != '+' && cmd[*i] != '=' && cmd[*i] != ' ')
	{
		if(cmd[*i] == 34)
			*i = get_name_from_double_quot(cmd, &name, *i, full_cmd);
		else if(cmd[*i] == 39 )
			*i = get_name_from_simple_quot(cmd, &name, *i, full_cmd);
		else
		{
			if(!ft_isalnum(cmd[*i]))
			{
				ft_putstr_fd("minishell: export: not a valid identifier", full_cmd->outf_fd);
					ft_putstr_fd("\n", full_cmd->outf_fd);
					return NULL; 
			}
			name = ft_strjoin_char(name, cmd[(*i)++]);
		}   display_export(full_cmd);
	}
	return name;
}

int get_value_too(char *cmd, int i, char **value)
{
	i++;
	while(cmd[i] && cmd[i] != 32)
	{
		if(cmd[i] == 34)
		{
			i++;
			while(cmd[i] && cmd[i] != 34 )
				*value = ft_strjoin_char(*value, cmd[i++]);
			i++;
		} 
		else if(cmd[i] == 39)
		{
			i++;
			while(cmd[i] && cmd[i] != 39 )
				*value = ft_strjoin_char(*value, cmd[i++]);
			i++;
		}
		else 
			*value = ft_strjoin_char(*value, cmd[i++]);
	}
	return i;
}

int add_to_export(char *cmd, int i, t_node *full_cmd, char *name)
{
	t_env *tmp2;
	
	tmp2 = g_gb.my_export;
	while(cmd[i] && cmd[i] == 32)
		i++;
	if(cmd[i] && !ft_isalnum(cmd[i]))
	{
		ft_putstr_fd("not a valid identifier", full_cmd->outf_fd );
		ft_putstr_fd("\n", full_cmd->outf_fd );
		return 0;
	}
	if(!name_is_exist_in_export(expend_herdocc(name)))
		ft_lstadd_back_env(&tmp2, ft_lstnew_env(expend_herdocc(name), "" , 0, existe_spaces("")));
	free(name);
	if(cmd[i])    
		i++;
	return i;
}


void  add_to_env_exp(char *name, char *value, int plus)
{
	t_env *tmp;
	
	tmp = g_gb.my_env;
	if(name_is_exist_in_env(name))
	{
		while(tmp)
		{
			if(!ft_strcmp(name, tmp->name))
			{
				if(plus)
					tmp->value = ft_strjoin(tmp->value, value);
				else
					tmp->value = value;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		ft_lstadd_back_env(&g_gb.my_env, ft_lstnew_env(expend_herdocc(name), expend_herdocc(value) , 1, existe_spaces(value)));
		ft_lstadd_back_env(&g_gb.my_export, ft_lstnew_env(expend_herdocc(name), expend_herdocc(value), 1, existe_spaces(value)));
	}
	free(name);
	free(value);
}

int add_value_in_lists(char *cmd, int i, char *name, t_node *full_cmd )
{
	int plus;
	char *value = NULL;

	plus = 0;
	value = NULL;
	if(cmd[i] == ' ' || cmd[i] == '\0')
		i = add_to_export(cmd, i, full_cmd, name);
	else 
	{
		if(cmd[i] == '+')
		{
			i++;
			plus = 1;
			if(cmd[i] != '=')
			{
				ft_putstr_fd("not a valid identifier", full_cmd->outf_fd );
				ft_putstr_fd("\n", full_cmd->outf_fd );
				return 0;
			}
		}
		i = get_value_too(cmd, i, &value);
		add_to_env_exp(name, value, plus);
	} 
	return i;
}

void ft_export(t_node *full_cmd)
{
	char *name ;
	char *cmd;
	int i;
	
	name = NULL;
	i = 0;
	cmd = &(full_cmd->cmd[6]);
	if(!cmd[0])
		display_export(full_cmd);
	while(cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
			i = skip_of(cmd, i);   
		else if (cmd[i] == ' ')
			while(cmd[i] && (cmd[i] == 32 || cmd[i] == '\t'))
				i++;
		else
		{
			name = get_namee(cmd, &i, full_cmd);
			i = add_value_in_lists(cmd, i, name, full_cmd);
			name = NULL;
		}
	}
	g_gb.exit_code = 0;
}


