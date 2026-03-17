/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2026/03/17 18:10:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_to_fd(char *limiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	apply_input_redir(t_cmd *cmd)
{
	int	fd;

	if (!cmd->input_file)
		return (0);
	if (cmd->heredoc)
		fd = heredoc_to_fd(cmd->input_file);
	else
		fd = open(cmd->input_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	apply_output_redir(t_cmd *cmd)
{
	int	fd;

	if (!cmd->output_file)
		return (0);
	if (cmd->append)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (last_status);
}

int	exec(t_cmd *cmd_tabl, t_shell *data)
{
	t_cmd	*cur;
	char	**env;
	int		pipefd[2];
	int		prev_read;
	pid_t	last_pid;

	cur = cmd_tabl;
	env = env_to_tab(data->envp);
	prev_read = -1;
	last_pid = -1;
	while (cur)
	{
		if (cur->next && pipe(pipefd) == -1)
			return (free_dtab(env), 1);
		last_pid = fork();
		if (last_pid == -1)
			return (free_dtab(env), 1);
		if (last_pid == 0)
		{
			if (prev_read != -1 && dup2(prev_read, STDIN_FILENO) == -1)
				hdl_error("dup2", errno);
			if (cur->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
				hdl_error("dup2", errno);
			if (prev_read != -1)
				close(prev_read);
			if (cur->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (apply_input_redir(cur) == -1 || apply_output_redir(cur) == -1)
				hdl_error("redir", errno);
			if (!cur->args || !cur->args[0])
				_exit(0);
			exec_cmd(cur->args, env);
		}
		if (prev_read != -1)
			close(prev_read);
		if (cur->next)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
		cur = cur->next;
	}
	if (prev_read != -1)
		close(prev_read);
	data->last_status = wait_pipeline(last_pid);
	free_dtab(env);
	return (data->last_status);
}
