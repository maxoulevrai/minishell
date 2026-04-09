/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:10:37 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:10:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	check_limits(char *str)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if ((sign == -1 && nb > (unsigned long long)LLONG_MAX + 1)
			|| (sign == 1 && nb > (unsigned long long)LLONG_MAX))
			return (0);
		i++;
	}
	return (1);
}

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

static int	check_exit_args(t_shell *data, t_cmd *cmd_tbl)
{
	int	exit_code;

	if (!cmd_tbl->args[1])
	{
		close(data->save_in);
		close(data->save_out);
		free_cmd_list(cmd_tbl);
		free_data(data);
		ft_fprintf(STDOUT_FILENO, "exit\n");
		exit(0);
	}
	if (!is_numeric(cmd_tbl->args[1]) || !check_limits(cmd_tbl->args[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n",
			cmd_tbl->args[1]);
		return (2);
	}
	if (cmd_tbl->args[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	exit_code = (((ft_atol(cmd_tbl->args[1]) % 256) + 256) % 256);
	return (exit_code);
}

// commande exit
// prototype: exit [n]
// sans argument -> exit avec code 0
// avec argument -> exit avec le code donné (0-255)
// trop d'arguments -> erreur, ne quitte pas

int	ft_exit(t_shell *data, t_cmd *cmd_tbl)
{
	long	exit_code;

	if (cmd_tbl->next)
		return (0);
	exit_code = check_exit_args(data, cmd_tbl);
	if (exit_code == 1)
		return (1);
	close(data->save_in);
	close(data->save_out);
	free_data(data);
	free_cmd_list(cmd_tbl);
	ft_fprintf(STDOUT_FILENO, "exit\n");
	exit(exit_code);
}
