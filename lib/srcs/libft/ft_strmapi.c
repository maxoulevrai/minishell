/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:38:29 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:09:03 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *src, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dst;

	if (!src)
		return (NULL);
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = (*f)(i, src[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
