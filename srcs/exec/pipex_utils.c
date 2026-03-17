/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:17:04 by maleca            #+#    #+#             */
/*   Updated: 2026/03/17 18:10:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hdl_error(char *arg, int err_code)
{
	if (arg)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", arg, strerror(err_code));
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s\n", strerror(err_code));
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

void	exec_cmd(char **args, char **env)
{
	char	*path;

	if (!args || !args[0])
	{
		ft_fprintf(STDERR_FILENO, "minishell: empty command\n");
		_exit(127);
	}
	path = get_path(args[0], env);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "minishell: command not found: %s\n", args[0]);
		_exit(127);
	}
	execve(path, args, env);
	free(path);
	hdl_error(args[0], errno);
}

char	**env_to_tab(t_env *envp)
{
	char	**env;
	char	*tmp;
	t_env	*cur;
	int		len;
	int		i;

	len = 0;
	cur = envp;
	while (cur && ++len)
		cur = cur->next;
	env = ft_calloc(len + 1, sizeof(char *));
	if (!env)
		return (NULL);
	cur = envp;
	i = 0;
	while (i < len)
	{
		tmp = ft_strjoin(cur->key, "=");
		if (!tmp)
			return (free_dtab(env), NULL);
		if (cur->value)
			env[i] = ft_strjoin(tmp, cur->value);
		else
			env[i] = ft_strdup(tmp);
		free(tmp);
		if (!env[i])
			return (free_dtab(env), NULL);
		cur = cur->next;
		i++;
	}
	return (env);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*next;

	while (cmd_list)
	{
		next = cmd_list->next;
		if (cmd_list->args)
			free_dtab(cmd_list->args);
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list);
		cmd_list = next;
	}
}
