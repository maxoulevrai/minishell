/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:37:19 by maleca            #+#    #+#             */
/*   Updated: 2025/09/07 20:40:10 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H

# define FT_FPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int		ft_fprintf(const int fd, const char *str, ...);
void	ft_putcharf_fd(char c, size_t *count, int fd);
void	ft_putstrf_fd(char *str, size_t *count, int fd);
void	ft_putnbrf_fd(int n, size_t *count, int fd);
void	ft_putaddyf_fd(unsigned long long adresse, size_t *count, int fd);
void	ft_putnbr_basef_fd(unsigned long long nb,
			char ind, size_t *count, int fd);

#endif