/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:04:30 by root              #+#    #+#             */
/*   Updated: 2026/03/27 16:39:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	ft_putstr_echo(char **t_cmd, int i)
{
	// int	i;
	int	j;

	// i = 0;
	while (t_cmd[i])
	{
		j = 0;
		while (t_cmd[i][j])
		{
			if (t_cmd[i][j] == '\\')
				j++;
			if (t_cmd[i][j])
			{
				write(STDOUT_FILENO, &t_cmd[i][j], 1);
				j++;
			}
		}
		if (t_cmd[i + 1])
			ft_fprintf(STDOUT_FILENO, " ");
		i++;
	}
}


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
	ft_putstr_echo(t_cmd, i);
	if (newline)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (0);
}
