/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:37:19 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 16:14:48 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putcharf(char c, size_t *count);
void	ft_putstrf(char *str, size_t *count);
void	ft_putnbrf(int n, size_t *count);
void	ft_putaddyf(unsigned long long adresse, size_t *count);
void	ft_putnbr_basef(unsigned long long nb, char *base, size_t *count);

#endif