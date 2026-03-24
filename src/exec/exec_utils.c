/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:17:04 by maleca            #+#    #+#             */
/*   Updated: 2026/03/23 14:53:58 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	hdl_error(char *arg, int err_code)
{
	if (arg)
		ft_fprintf(STDERR_FILENO, "6ft shell: %s: %s\n",
			arg, strerror(err_code));
	else
		ft_fprintf(STDERR_FILENO, "6ft shell: %s\n", strerror(err_code));
	_exit(err_code);
}

char	**get_path_list(t_env *env)
{
	char	**path_list;
	char	*path_var;

	if (!env)
		return (NULL);
	path_var = get_env(&env, "PATH");
	if (!path_var)
		return (NULL);
	path_list = ft_split(path_var, ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**path_list;
	char	*tmp;
	char	*ret;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path_list = get_path_list(env);
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, F_OK | X_OK) == 0)
			return (free_dtab(path_list), ret);
		free(ret);
		i++;
	}
	free_dtab(path_list);
	return (NULL);
}

void	exec_cmd(t_cmd *cmd, t_shell *data)
{
	char	*path;
	char	**env_tabl;

	if (!cmd || !cmd->args[0])
		return (ft_fprintf(STDERR_FILENO, "6ft shell: : command not found\n"),
			_exit(127));
	if (is_child_builtin(cmd->args[0]))
	{
		builtins_dispatcher(data, cmd);
		return (free_cmd_list(cmd), _exit(0));
	}
	env_tabl = env_to_tab(data->envp);
	path = get_path(cmd->args[0], data->envp);
	if (!path)
		return (free_dtab(env_tabl),
			ft_fprintf(STDERR_FILENO, "6ft shell: %s: command not found\n",
				cmd->args[0]), _exit(127));
	if (execve(path, cmd->args, env_tabl) == -1)
	{
		free(path);
		free_dtab(env_tabl);
		free_cmd_list(cmd);
		hdl_error(NULL, errno);
	}
}
