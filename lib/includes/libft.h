/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:58:33 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:40:14 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>

# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t siz);
int		ft_memcmp(const void *s1, const void *s2, size_t siz);
int		ft_atoi(const char *nptr);
long	ft_abs(long nbr);
long	ft_atol(const char *nptr);
void	free_dtab(char **dtab);
void	ft_bzero(void *ptr, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *src, void (*f)(unsigned int, char*));
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *ptr, int val, size_t siz);
void	*ft_memchr(const void *ptr, int val, size_t siz);
void	*ft_memcpy(void *dst, const void *src, size_t siz);
void	*ft_memmove(void *dst, const void *src, size_t siz);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_strcat(char *dst, char *src);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(const char *src, const char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *src, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t siz);
char	**ft_split(const char *str, char c);
size_t	get_dtab_len(char **dtab);
size_t	ft_strlen(const char *str);
size_t	word_len(const char *str, char c);
size_t	word_count(const char *str, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));

#endif