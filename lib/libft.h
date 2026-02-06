/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:58:33 by maleca            #+#    #+#             */
/*   Updated: 2025/08/05 22:41:34 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

int		ft_printf(const char *str, ...);
void	ft_putcharf(char c, size_t *count);
void	ft_putstrf(char *str, size_t *count);
void	ft_putnbrf(int n, size_t *count);
void	ft_putaddyf(unsigned long long adresse, size_t *count);
void	ft_putnbr_basef(unsigned long long nb, char *base, size_t *count);

size_t	gnl_len(char *str);
void	stash_cleanup(char **stash);
char	*get_next_line(int fd);
char	*ft_strchr_gnl(char *str, char c);
char	*ft_strjoin_gnl(char *stash, char *buff);
char	*read_and_store(int fd, char *stash, int *flag);

#endif