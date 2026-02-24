/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_basef.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:51 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:03:41 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	ft_putnbr_basef(unsigned long long nb, char *base, size_t *count)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
		ft_putnbr_basef(nb / base_len, base, count);
	ft_putcharf(base[nb % base_len], count);
}
