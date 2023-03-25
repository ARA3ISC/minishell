/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:16:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/25 15:00:54 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	printf("%s\n", msg);
}

void	print_error_and_break(char *msg)
{
	printf("%s\n", msg);
	// break 
}
