/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:43:49 by maleca            #+#    #+#             */
/*   Updated: 2025/08/02 02:05:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_calloc(size_t nmemb, size_t siz)
{
	unsigned char	*ptr;

	if (siz && nmemb > (UINT_MAX / siz))
		return (NULL);
	ptr = malloc(nmemb * siz);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * siz);
	return (ptr);
}
