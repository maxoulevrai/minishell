/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:07:45 by root              #+#    #+#             */
/*   Updated: 2025/08/22 21:55:43 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *stash, char *buf)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = ft_calloc(1, sizeof(char));
		if (!stash)
			return (NULL);
	}
	new_stash = malloc(sizeof(char)
			*(ft_strlen_gnl(stash) + ft_strlen_gnl(buf) + 1));
	if (!new_stash)
		return (NULL);
	i = -1;
	while (stash[++i])
		new_stash[i] = stash[i];
	j = 0;
	while (buf[j])
		new_stash[i++] = buf[j++];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

void	stash_cleanup(char **stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	if (!*stash || !ft_strchr_gnl(*stash, '\n'))
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	new_stash = malloc(sizeof(char) * (ft_strlen_gnl(*stash) - i + 1));
	if (!new_stash)
		return ;
	j = 0;
	while ((*stash)[++i])
		new_stash[j++] = (*stash)[i];
	new_stash[j] = '\0';
	free(*stash);
	*stash = new_stash;
}
