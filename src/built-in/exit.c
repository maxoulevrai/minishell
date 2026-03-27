/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:04:50 by root              #+#    #+#             */
/*   Updated: 2026/03/27 16:28:31 by root             ###   ########.fr       */
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

static int	check_exit_args(t_shell *data, t_cmd *cmd_tbl)
{
	if (!cmd_tbl->args[1])
	{
		close(data->save_in);
		close(data->save_out);
		free_cmd_list(cmd_tbl);
		free_data(data);
		exit(0);
	}
	if (cmd_tbl->args[2])
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (data->last_status = 1, 1);
	}
	if (!is_numeric(cmd_tbl->args[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", cmd_tbl->args[1]);
		return (data->last_status = 2, 2);
	}
	return (0);
}

// commande exit
// prototype: exit [n]
// sans argument -> exit avec code 0
// avec argument -> exit avec le code donné (0-255)
// trop d'arguments -> erreur, ne quitte pas

int	ft_exit(t_shell *data, t_cmd *cmd_tbl)
{
	long	exit_code;

	if (check_exit_args(data, cmd_tbl))
		return (data->last_status);
	exit_code = (ft_atol(cmd_tbl->args[1]) % 256) + 256;
	close(data->save_in);
	close(data->save_out);
	free_data(data);
	free_cmd_list(cmd_tbl);
	exit(exit_code);
}
