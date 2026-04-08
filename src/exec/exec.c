/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:45:02 by root              #+#    #+#             */
/*   Updated: 2026/04/06 19:47:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static pid_t	spawn_cmd(t_cmd *cur, t_shell *data,
		t_cmd *cmd_head, int prev_read, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_process(cur, cmd_head, data, prev_read, pipefd);
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

static int	collect_heredoc(t_cmd *cmd_tbl)
{
	t_cmd	*cur;
	t_cmd	*prev;

	cur = cmd_tbl;
	while (cur)
	{
		if (cur->heredoc)
		{
			cur->heredoc_fd = heredoc_to_fd(cur->input_file);
			if (cur->heredoc_fd == -1)
			{
				prev = cmd_tbl;
				while (prev != cur)
				{
					if (prev->heredoc && prev->heredoc_fd > STDERR_FILENO)
						(close(prev->heredoc_fd), prev->heredoc_fd = -1);
					prev = prev->next;
				}
				return (-1);
			}
		}
		cur = cur->next;
	}
	return (0);
}

static int	exec_loop(t_shell *data, t_cmd *cmd_tbl)
{
	t_cmd	*cur;
	pid_t	last_pid;
	int		prev_read;
	int		pipefd[2];

	cur = cmd_tbl;
	prev_read = -1;
	while (cur)
	{
		if (cur->next && pipe(pipefd) == -1)
			return (init_signal(), -1);
		last_pid = spawn_cmd(cur, data, cmd_tbl, prev_read, pipefd);
		if (last_pid == -1)
			return (init_signal(), -1);
		update_parent_pipe(cur, &prev_read, pipefd);
		cur = cur->next;
	}
	if (prev_read != -1)
		close(prev_read);
	return (last_pid);
}

int	exec(t_cmd *cmd_tbl, t_shell *data)
{
	pid_t	last_pid;

	if (collect_heredoc(cmd_tbl) == -1)
		return (data->last_status = 130, 130);
	if (cmd_tbl && !cmd_tbl->next && cmd_tbl->args
		&& is_parent_builtin(cmd_tbl->args[0]))
		return (exec_parent_builtin(cmd_tbl, data));
	last_pid = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	last_pid = exec_loop(data, cmd_tbl);
	if (last_pid == -1)
		return (1);
	data->last_status = wait_pipeline(last_pid);
	return (init_signal(), data->last_status);
}
