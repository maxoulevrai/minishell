/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddyf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:43 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:03:41 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

void	ft_putaddyf(unsigned long long adresse, size_t *count)
{
	if (!adresse)
	{
		ft_putstrf("(nil)", count);
		return ;
	}
	ft_putstrf("0x", count);
	ft_putnbr_basef(adresse, "0123456789abcdef", count);
}
