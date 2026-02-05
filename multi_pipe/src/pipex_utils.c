/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:17:04 by maleca            #+#    #+#             */
/*   Updated: 2025/09/19 19:18:53 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_exit(void)
{
	int		status;
	int		last_status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	if (last_status != 0)
		exit(last_status);
}

void	hdl_error(char *arg, int err_code)
{
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", strerror(err_code), arg);
	_exit(err_code);
}

char	**get_path_list(char **env)
{
	char	**path_list;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path_list = ft_split(&env[i][5], ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

char	*get_path(char *cmd, char **env)
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

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		if (s_cmd)
			free(s_cmd);
		ft_fprintf(STDERR_FILENO, "pipex: invalid command: %s\n", cmd);
		_exit(127);
	}
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		free_dtab(s_cmd);
		ft_fprintf(STDERR_FILENO, "pipex: invalid command: %s\n", cmd);
		_exit(127);
	}
	execve(path, s_cmd, env);
	free(path);
	free_dtab(s_cmd);
	hdl_error(NULL , 127);
}
