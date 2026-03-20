/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:08:16 by root              #+#    #+#             */
/*   Updated: 2026/03/19 17:22:47 by root             ###   ########.fr       */
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

int	ft_exit(char **cmd)
{
	long	exit_code;

	ft_fprintf(STDOUT_FILENO, "exit\n");
	if (!cmd[1])
		exit(0);
	if (cmd[2])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (1);
	}
	if (!is_numeric(cmd[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"exit: %s: numeric argument required\n", cmd[1]);
		exit(2);
	}
	exit_code = ft_atol(cmd[1]);
	exit(exit_code % 256);
}
