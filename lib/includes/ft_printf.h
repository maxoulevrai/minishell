/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:37:19 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:18:26 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
void	ft_putcharf(char c, size_t *count);
void	ft_putstrf(char *str, size_t *count);
void	ft_putnbrf(int n, size_t *count);
void	ft_putaddyf(unsigned long long adresse, size_t *count);
void	ft_putnbr_basef(unsigned long long nb, char *base, size_t *count);

#endif