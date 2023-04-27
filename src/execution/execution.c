/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:54:30 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/27 13:15:28 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void execution(t_node *list_cmd)
{
	if (ft_lstsize(list_cmd) == 1)
	{
		if (is_builtin(list_cmd))
			printf("builtin\n");
		else
			printf("mashi builtin\n");
			// execution
	}
	else if (ft_lstsize(list_cmd) > 1)
	{
		// fork
	}
}
