/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:15:21 by maleca            #+#    #+#             */
/*   Updated: 2025/08/08 19:36:46 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

long	ft_nbrlen(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*convert;
	long	nb;
	long	len;

	nb = (long)n;
	len = ft_nbrlen(nb);
	convert = malloc(sizeof(char) * (len + 1));
	if (!convert)
		return (NULL);
	convert[len--] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		convert[0] = '-';
	}
	if (nb == 0)
		convert[0] = '0';
	while (nb > 0)
	{
		convert[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (convert);
}
