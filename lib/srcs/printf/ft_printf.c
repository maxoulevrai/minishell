/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:46:26 by maleca            #+#    #+#             */
/*   Updated: 2025/05/07 14:56:59 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert(char format, va_list args, size_t *count)
{
	if (format == 'c')
		ft_putcharf(va_arg(args, int), count);
	else if (format == 's')
		ft_putstrf(va_arg(args, char *), count);
	else if (format == 'p')
		ft_putaddyf(va_arg(args, unsigned long long), count);
	else if (format == 'd' || format == 'i')
		ft_putnbrf(va_arg(args, int), count);
	else if (format == 'u')
		ft_putnbr_basef(va_arg(args, unsigned int), "0123456789", count);
	else if (format == 'x')
		ft_putnbr_basef(va_arg(args, unsigned int), "0123456789abcdef", count);
	else if (format == 'X')
		ft_putnbr_basef(va_arg(args, unsigned int), "0123456789ABCDEF", count);
	else if (format == '%')
		ft_putcharf('%', count);
	else
	{
		ft_putcharf('%', count);
		ft_putcharf(format, count);
	}
}

int	ft_printf(const char *param, ...)
{
	va_list		args;
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	va_start(args, param);
	while (param[i])
	{
		if (param[i] == '%')
		{
			ft_convert(param[i + 1], args, &count);
			i += 2;
		}
		else
		{
			ft_putcharf(param[i], &count);
			i++;
		}
	}
	va_end(args);
	return (count);
}
