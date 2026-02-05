/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:05:09 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:17:27 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# include <unistd.h>
# include <stdio.h>
# include "libft.h"

char	*get_next_line(int fd, char *LIMITER);
char	*ft_strchr_gnl(char *str, char c);
void	stash_cleanup(char **stash);
char	*read_and_store(int fd, char *stash, int *flag);
size_t	gnl_len(char *str);
char	*ft_strjoin_gnl(char *stash, char *buff);

#endif