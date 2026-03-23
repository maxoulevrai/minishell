/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:34:22 by maleca            #+#    #+#             */
/*   Updated: 2026/03/19 17:22:47 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// verifie la validité du flag -n
// return 1 si flag valide sinon 0
// (-n, -nn, -nnn, etc sont valide)

static int	is_n_flag(char *flag)
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
	int	newline;

	newline = TRUE;
	i = 1;
	while (t_cmd[i] && is_n_flag(t_cmd[i]))
	{
		newline = FALSE;
		i++;
	}
	while (t_cmd[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s", t_cmd[i]);
		if (t_cmd[i + 1])
			ft_fprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (newline)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (0);
}
