/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:28:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/25 14:38:29 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (s != NULL)
	{
		len = ft_strlen(s);
		while (i <= len)
		{
			if (s[i] == (char)c)
			{
				return ((char *)s + i);
			}
			i++;
		}
	}
	return (NULL);
}
