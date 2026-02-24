/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 04:02:59 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:03:58 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_fprintf.h"

void	ft_putstrf_fd(char *str, size_t *count, int fd)
{
	int	i;

	if (!str)
	{
		ft_putstrf_fd("(null)", count, fd);
		return ;
	}
	i = 0;
	while (str[i])
	{
		(*count)++;
		i++;
	}
	write(fd, str, i);
}
