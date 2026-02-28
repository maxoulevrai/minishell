/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:53 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 16:54:11 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strndup(const char *src, size_t siz)
{
	char	*dst;
	size_t	i;

	dst = malloc(sizeof(char) * (siz + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && i < siz)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
