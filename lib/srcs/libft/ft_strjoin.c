/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:00:49 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:09:03 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined_args;
	int		i;
	int		j;

	i = -1;
	j = 0;
	joined_args = NULL;
	if (!s1 && !s2)
		return (NULL);
	joined_args = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined_args)
		return (NULL);
	while (s1[++i] && *s1)
		joined_args[i] = s1[i];
	while (s2[j])
		joined_args[i++] = s2[j++];
	joined_args[i] = '\0';
	return (joined_args);
}
