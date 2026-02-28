/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_basef_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:51 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:39:46 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_fprintf.h"

static char	*get_base(char ind)
{
	if (ind == 'u')
		return ("0123456789");
	else if (ind == 'x')
		return ("0123456789abcdef");
	else if (ind == 'X')
		return ("0123456789ABCDEF");
	return (NULL);
}

void	ft_putnbr_basef_fd(unsigned long long nb,
			char ind, size_t *count, int fd)
{
	size_t	base_len;
	char	*base;

	base = get_base(ind);
	base_len = ft_strlen(base);
	if (nb >= base_len)
		ft_putnbr_basef_fd(nb / base_len, ind, count, fd);
	ft_putcharf_fd(base[nb % base_len], count, fd);
}
