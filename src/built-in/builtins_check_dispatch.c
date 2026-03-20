/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check_dispatch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:40:58 by root              #+#    #+#             */
/*   Updated: 2026/03/20 04:35:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Commandes a reproduires:
// - pwd with no options
// - export with no options
// - unset with no options
// - env with no options or arguments
// - exit with no options
// - echo with option -n
// - cd with only a relative or absolute path

int	builtins_checker(char *arg)
{
	if (!arg[0])
		return (FALSE);
	else if (!ft_strcmp(arg, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(arg, "export"))
		return (TRUE);
	else if (!ft_strcmp(arg, "unset"))
		return (TRUE);
	else if (!ft_strcmp(arg, "env"))
		return (TRUE);
	else if (!ft_strcmp(arg, "exit"))
		return (TRUE);
	else if (!ft_strcmp(arg, "echo"))
		return (TRUE);
	else if (!ft_strcmp(arg, "cd"))
		return (2);
	else
		return (FALSE);
}

int	builtins_dispatcher(t_env *envp, char **args)
{
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(envp, args));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(envp, args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(envp, args));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(envp, args));
	else
		return (1);
}
