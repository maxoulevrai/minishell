/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check_dispatch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:40:58 by root              #+#    #+#             */
/*   Updated: 2026/02/28 15:22:45 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bultins.h"

// Commandes a reproduires:
// - pwd with no options
// - export with no options
// - unset with no options
// - env with no options or arguments
// - exit with no options
// - echo with option -n
// - cd with only a relative or absolute path

int	builtins_checker(char *t_cmd)
{
	if (!t_cmd)
		return (FAILURE);
	else if (!ft_strcmp(t_cmd, "pwd"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "export"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "unset"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "env"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "exit"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "echo"))
		return (SUCCESS);
	else if (!ft_strcmp(t_cmd, "cd"))
		return (2);
	else
		return (FAILURE);
}

int	builtins_dispatcher(char **t_cmd)
{
	if (!ft_strcmp(t_cmd, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(t_cmd, "export"))
		return (ft_export());
	else if (!ft_strcmp(t_cmd, "unset"))
		return (ft_unset());
	else if (!ft_strcmp(t_cmd, "env"))
		return (ft_env());
	else if (!ft_strcmp(t_cmd, "exit"))
		return (ft_exit());
	else if (!ft_strcmp(t_cmd, "echo"))
		return (ft_echo());
	else if (!ft_strcmp(t_cmd, "cd"))
		return (ft_cd());
	else
		return (FAILURE);
}
