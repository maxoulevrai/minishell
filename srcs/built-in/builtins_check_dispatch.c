/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check_dispatch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:40:58 by root              #+#    #+#             */
/*   Updated: 2026/02/24 16:12:28 by root             ###   ########.fr       */
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
		return (FALSE);
	else if (!ft_strcmp(t_cmd, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "export"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "unset"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "env"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "exit"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "echo"))
		return (TRUE);
	else if (!ft_strcmp(t_cmd, "cd"))
		return (2);
	else
		return (FALSE);
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
		return (FALSE);
}
