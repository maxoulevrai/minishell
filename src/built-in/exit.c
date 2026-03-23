/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:08:16 by maleca             #+#    #+#             */
/*   Updated: 2026/03/23 14:57:16 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// vérifie si la string est un nombre valide
// return 1 si valide, 0 sinon

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// commande exit
// prototype: exit [n]
// sans argument -> exit avec code 0
// avec argument -> exit avec le code donné (0-255)
// trop d'arguments -> erreur, ne quitte pas

int	ft_exit(t_shell *data, char **cmd)
{
	long	exit_code;

	if (!cmd[1])
	{
		free_data(data);
		exit(0);
	}
	if (cmd[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		free_data(data);
		return (1);
	}
	if (!is_numeric(cmd[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", cmd[1]);
		free_data(data);
		exit(2);
	}
	exit_code = ft_atol(cmd[1]);
	free_data(data);
	exit(exit_code % 256);
}
