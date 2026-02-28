/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 04:04:54 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:03:58 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_fprintf.h"

void	ft_putnbrf_fd(int n, size_t *count, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		nb *= -1;
		ft_putcharf_fd('-', count, fd);
	}
	if (nb > 9)
	{
		ft_putnbrf_fd(nb / 10, count, fd);
		ft_putcharf_fd(nb % 10 + '0', count, fd);
	}
	else
		ft_putcharf_fd(nb % 10 + '0', count, fd);
}
