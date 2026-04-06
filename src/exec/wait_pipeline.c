/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:19:19 by root              #+#    #+#             */
/*   Updated: 2026/04/06 19:34:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	hdl_lastpid(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (128 + sig);
	}
	return (0);
}

int	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0 || (pid == -1 && errno == EINTR))
	{
		if (pid == -1)
		{
			pid = wait(&status);
			continue ;
		}
		if (pid == last_pid)
			last_status = hdl_lastpid(status);
		pid = wait(&status);
	}
	return (last_status);
}
