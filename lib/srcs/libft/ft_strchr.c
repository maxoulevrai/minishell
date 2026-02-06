/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:11:05 by maleca            #+#    #+#             */
/*   Updated: 2025/08/02 02:05:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strchr(const char *str, int val)
{
	size_t	i;
	char	c;

	i = 0;
	c = (char)val;
	while (str[i])
	{
		if (str[i] == c)
			return (((char *)&str[i]));
		i++;
	}
	if (c == '\0')
		return (((char *)&str[i]));
	return (NULL);
}
