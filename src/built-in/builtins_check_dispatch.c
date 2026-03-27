/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check_dispatch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:10:32 by root              #+#    #+#             */
/*   Updated: 2026/03/27 14:58:38 by root             ###   ########.fr       */
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

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	is_child_builtin(char *cmd)
{
	if (!cmd[0])
		return (FALSE);
	else if (!ft_strcmp(cmd, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "env"))
		return (TRUE);
	else if (!ft_strcmp(cmd, "echo"))
		return (TRUE);
	else
		return (FALSE);
}

int	builtins_dispatcher(t_shell *data, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(data->envp, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(data->envp, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(data->envp, cmd->args));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(data, cmd));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(data->envp, cmd->args));
	else
		return (1);
}
