/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:06:27 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:06:33 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	line = NULL;
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
	if ((*stash)[i] == '\n')
		i++;
	new_stash = malloc(sizeof(char) * (gnl_len(*stash) - i + 1));
	if (!new_stash)
		return ;
	j = 0;
	while ((*stash)[i])
		new_stash[j++] = (*stash)[i++];
	new_stash[j] = '\0';
	free(*stash);
	*stash = new_stash;
}

char	*read_and_store(int fd, char *stash, int *flag)
{
	char		*buff;
	ssize_t		read_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr_gnl(stash, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), NULL);
		buff[read_bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
		if (!stash)
			return (free(buff), NULL);
	}
	if (read_bytes == 0)
		*flag = 1;
	free(buff);
	return (stash);
}

char	*get_next_line(int fd, char *LIMITER)
{
	static char	*stash;
	char		*next_line;
	int			flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	flag = 0;
	stash = read_and_store(fd, stash, &flag);
	if (!stash)
		return (free(stash), NULL);
	next_line = extract_line(stash);
	stash_cleanup(&stash);
	if (flag == 1 || !ft_strncmp(next_line, LIMITER, ft_strlen(LIMITER)))
		free(stash);
	return (next_line);
}
