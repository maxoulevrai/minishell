/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:20:26 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:37:32 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fprintf.h"

static void	ft_convert(char format, va_list args, size_t *count, int fd)
{
	if (format == 'c')
		ft_putcharf_fd(va_arg(args, int), count, fd);
	else if (format == 's')
		ft_putstrf_fd(va_arg(args, char *), count, fd);
	else if (format == 'p')
		ft_putaddyf_fd(va_arg(args, unsigned long long), count, fd);
	else if (format == 'd' || format == 'i')
		ft_putnbrf_fd(va_arg(args, int), count, fd);
	else if (format == 'u')
		ft_putnbr_basef_fd(va_arg(args, unsigned int), 'u', count, fd);
	else if (format == 'x')
		ft_putnbr_basef_fd(va_arg(args, unsigned int), 'x', count, fd);
	else if (format == 'X')
		ft_putnbr_basef_fd(va_arg(args, unsigned int), 'X', count, fd);
	else if (format == '%')
		ft_putcharf_fd('%', count, fd);
	else
	{
		ft_putcharf_fd('%', count, fd);
		ft_putcharf_fd(format, count, fd);
	}
}

int	ft_fprintf(const int fd, const char *param, ...)
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
			ft_convert(param[i + 1], args, &count, fd);
			i += 2;
		}
		else
		{
			ft_putcharf_fd(param[i], &count, fd);
			i++;
		}
	}
	va_end(args);
	return (count);
}
