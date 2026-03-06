/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check_dispatch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:40:58 by root              #+#    #+#             */
/*   Updated: 2026/03/06 16:27:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"

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

int	builtins_dispatcher(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(*shell->envp, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(*shell->envp, cmd->args));
	else
		return (FALSE);
}
