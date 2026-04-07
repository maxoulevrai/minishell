/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:11:59 by root              #+#    #+#             */
/*   Updated: 2026/04/06 19:00:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	hdl_sigint_heredoc(char *line, int *pipefd)
{
	free(line);
	close(pipefd[0]);
	close(pipefd[1]);
	g_signal = 0;
	init_signal();
}

int	heredoc_to_fd(char *limiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	g_signal = 0;
	set_signal_heredoc();
	rl_done = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal == SIGINT)
			return (hdl_sigint_heredoc(line, pipefd), -1);
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
	return (init_signal(), close(pipefd[1]), pipefd[0]);
}

static int	open_redir_fd(t_cmd *cmd, int i)
{
	if (cmd->redir_types[i] == REDIR_IN)
		return (open(cmd->redir_files[i], O_RDONLY));
	if (cmd->redir_types[i] == REDIR_OUT)
		return (open(cmd->redir_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (cmd->redir_types[i] == REDIR_APPEND)
		return (open(cmd->redir_files[i], O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (cmd->heredoc_fd);
}

static int	dup_redir_fd(int fd, int type)
{
	if (type == REDIR_IN || type == HERE_DOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), -1);
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}

int	apply_redirs(t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		fd = open_redir_fd(cmd, i);
		if (fd < 0)
			return (-1);
		if (dup_redir_fd(fd, cmd->redir_types[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
