/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:33 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/12 15:39:20 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	banner(void)
{
	printf("\n");
	printf(GREEN "\t|███    ███ ██ ███    ██ ██ █████"
		"██ ██   ██ ███████ ██      ██| \n");
	printf("\t|████  ████ ██ ████   ██ ██ ██   "
		"   ██   ██ ██      ██      ██|  \n");
	printf("\t|██ ████ ██ ██ ██ ██  ██ ██ █████"
		"██ ███████ █████   ██      ██|\n");
	printf("\t|██  ██  ██ ██ ██  ██ ██ ██      "
		"██ ██   ██ ██      ██      ██| \n");
	printf("\t|██      ██ ██ ██   ████ ██ █████"
		"██ ██   ██ ███████ ███████ ███████|\n" RESET);
	printf("\n");
}
