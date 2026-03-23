/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2026/03/23 14:54:55 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		last_status;
	int		sig;
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
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				else if (sig == SIGQUIT)
					write(STDERR_FILENO, "Quit (core dumped)\n", 19);
				last_status = 128 + sig;
			}
		}
		pid = wait(&status);
	}
	return (last_status);
}

static void	child_process(t_cmd *cur, t_shell *data,
		int prev_read, int pipefd[2])
{
	set_signal_exec_child();
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
	{
		if (g_signal == SIGINT)
			_exit(130);
		hdl_error("redir", errno);
	}
	if (!cur->args || !cur->args[0])
		_exit(0);
	exec_cmd(cur->args, data);
}

static pid_t	spawn_cmd(t_cmd *cur, t_shell *data,
		int prev_read, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_process(cur, data, prev_read, pipefd);
	return (pid);
}

static void	update_parent_pipe(t_cmd *cur, int *prev_read, int pipefd[2])
{
	if (*prev_read != -1)
		close(*prev_read);
	if (cur->next)
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
}

int	exec(t_cmd *cmd_tabl, t_shell *data)
{
	t_cmd	*cur;
	int		pipefd[2];
	int		prev_read;
	pid_t	last_pid;

	if (cmd_tabl && !cmd_tabl->next && cmd_tabl->args
		&& is_parent_builtin(cmd_tabl->args[0]))
		return (exec_parent_builtin(cmd_tabl, data));
	cur = cmd_tabl;
	prev_read = -1;
	last_pid = -1;
	set_signal_exec_parent();
	while (cur)
	{
		if (cur->next && pipe(pipefd) == -1)
			return (init_signal(), 1);
		last_pid = spawn_cmd(cur, data, prev_read, pipefd);
		if (last_pid == -1)
			return (init_signal(), 1);
		update_parent_pipe(cur, &prev_read, pipefd);
		cur = cur->next;
	}
	if (prev_read != -1)
		close(prev_read);
	data->last_status = wait_pipeline(last_pid);
	return (init_signal(), data->last_status);
}
