/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 04:04:54 by maleca            #+#    #+#             */
/*   Updated: 2025/05/03 17:09:23 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbrf(int n, size_t *count)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		nb *= -1;
		ft_putcharf('-', count);
	}
	if (nb > 9)
	{
		ft_putnbrf(nb / 10, count);
		ft_putcharf(nb % 10 + '0', count);
	}
	else
		ft_putcharf(nb % 10 + '0', count);
}
