/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddyf_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:43 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:37:49 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_fprintf.h"

void	ft_putaddyf_fd(unsigned long long adresse, size_t *count, int fd)
{
	if (!adresse)
	{
		ft_putstrf_fd("(nil)", count, fd);
		return ;
	}
	ft_putstrf_fd("0x", count, fd);
	ft_putnbr_basef_fd(adresse, 'x', count, fd);
}
