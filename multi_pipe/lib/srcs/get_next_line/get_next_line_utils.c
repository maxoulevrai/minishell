/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:06:41 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:06:50 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	gnl_len(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t siz)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (siz && nmemb > (UINT_MAX / siz))
		return (NULL);
	ptr = malloc(nmemb * siz);
	if (!ptr)
		return (NULL);
	while (i < nmemb * siz)
		ptr[i++] = 0;
	return (ptr);
}

char	*ft_strjoin_gnl(char *stash, char *buff)
{
	char	*new_stash;
	int		i;
	int		j;

	if (!stash)
	{
		stash = ft_calloc(1, sizeof(char));
		if (!stash)
			return (NULL);
	}
	new_stash = NULL;
	if (!stash && !buff)
		return (NULL);
	new_stash = malloc(sizeof(char) * (gnl_len(stash) + gnl_len(buff) + 1));
	if (!new_stash)
		return (NULL);
	i = -1;
	while (stash[++i] && *stash)
		new_stash[i] = stash[i];
	j = 0;
	while (buff[j])
		new_stash[i++] = buff[j++];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}
