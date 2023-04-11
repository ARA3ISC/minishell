/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:24:37 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/11 14:33:35 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && s1[i])
		str[i++] = s1[j++];
	j = 0;
	while (i < len)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	else if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && s1[i])
		str[i++] = s1[j++];
	j = 0;
	while (i < len)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
