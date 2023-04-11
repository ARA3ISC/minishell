/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:23:09 by eej-jama          #+#    #+#             */
/*   Updated: 2023/04/11 14:33:43 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int					ft_atoi(const char *str);
void				ft_bzero(void *s, int n);
void				*ft_calloc(int count, int size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, int n);
int					ft_memcmp(const void *s1, const void *s2, int n);
void				*ft_memcpy(void *dst, const void *src, int n);
void				*ft_memmove(void *dst, const void *src, int len);
void				*ft_memset(void *b, int c, int len);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
int				ft_strlcat(char *dst, const char *src, int dstsize);
int				ft_strlcpy(char *dst, const char *src, int dstsize);
int				ft_strlen(const char *s);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strnstr(const char *haystack, const char *needle,
						int len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_substr(char const *s,  int start, int len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin2(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_node;


#endif
