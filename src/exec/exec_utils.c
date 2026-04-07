/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:44:28 by root              #+#    #+#             */
/*   Updated: 2026/04/06 19:48:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	hdl_error(t_shell *data, t_cmd *cmd_tbl, char *arg, int err_code)
{
	free_data(data);
	free_cmd_list(cmd_tbl);
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

void	child_process(t_cmd *cur, t_shell *data,
		int prev_read, int pipefd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_read != -1 && dup2(prev_read, STDIN_FILENO) == -1)
		hdl_error(data, cur, "dup2", errno);
	if (cur->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
		hdl_error(data, cur, "dup2", errno);
	if (prev_read != -1)
		close(prev_read);
	if (cur->next)
		(close(pipefd[0]), close(pipefd[1]));
	if (apply_input_redir(cur) == -1 || apply_output_redir(cur) == -1)
		hdl_redir_error(cur, data);
	if (!cur->args || !cur->args[0])
		_exit(0);
	if (is_child_builtin(cur->args[0]))
	{
		builtins_dispatcher(data, cur);
		return (free_cmd_list(cur), free_data(data), _exit(0));
	}
	exec_cmd(cur, data);
}

void	exec_cmd(t_cmd *cmd, t_shell *data)
{
	char	*path;
	char	**env_tabl;

	if (!cmd || !cmd->args[0] || !cmd->args[0][0])
		return (ft_fprintf(STDERR_FILENO, "6ft shell: : command not found\n"),
			_exit(127));
	env_tabl = env_to_tab(data->envp);
	path = get_path(cmd->args[0], data->envp);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "6ft shell: %s: command not found\n",
			cmd->args[0]),
		free_dtab(env_tabl);
		free_cmd_list(cmd);
		free_data(data);
		_exit(127);
	}
	if (execve(path, cmd->args, env_tabl) == -1)
	{
		free(path);
		free_dtab(env_tabl);
		hdl_error(data, cmd, NULL, errno);
	}
}
