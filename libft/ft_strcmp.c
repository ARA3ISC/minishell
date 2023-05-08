/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:12:49 by maneddam          #+#    #+#             */
/*   Updated: 2023/05/07 14:41:42 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	if (!s1 || !s2)
		return (1);
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	while (ps1[i] || ps2[i])
	{
		if (ps1[i] != ps2[i])
			return (ps1[i] - ps2[i]);
		i++;
	}
	return (0);
}
