/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:34:22 by maleca            #+#    #+#             */
/*   Updated: 2026/02/24 16:14:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verifie la validité du flag -n
// return 1 si flag valide sinon 0
// (-n, -nn, -nnn, etc sont valide)

int	is_n_flag(char *flag)
{
	int	i;

	if (flag[0] != '-')
		return (0);
	i = 1;
	if (flag[i] == '\0')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// commande echo 
// prototype: echo [-n] [str]
// flag -n == pas de '\n' apres str

int	ft_echo(char **t_cmd)
{
	int	i;
	int newline;

	newline = TRUE;
	i = 0;
	if (!t_cmd[0])
		return (ft_fprintf("\n", 1), 1);
	while (is_n_flag(t_cmd[i]) && t_cmd[i])
	{
		newline = FALSE;
		i++;
	}
	ft_fprintf("%s", &t_cmd[1][i], 1);
	if (newline)
		ft_fprintf("\n", 1);
	return (0);
}
