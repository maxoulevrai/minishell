/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:52 by maleca            #+#    #+#             */
/*   Updated: 2025/09/16 16:24:00 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_tipeu1(char **av, char **env, int pipefd[2])
{
	int	fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		close(pipefd[1]);
		hdl_error(av[1], errno);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[1]);
	exec_cmd(av[2], env);
}

static void	ft_tipeu2(char **av, char **env, int pipefd[2])
{
	int	fd;

	close(pipefd[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(pipefd[0]);
		hdl_error(av[4], errno);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	close(pipefd[0]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	int		pid;

	if (ac < 5)
		return (ft_fprintf(STDERR_FILENO, "pipex: too few arguments\n"), EXIT_FAILURE);
	if (ac > 5)
		return (ft_fprintf(STDERR_FILENO, "pipex: too many arguments\n"), EXIT_FAILURE);
	errno = 0;
	if (pipe(pipefd) == -1)
		hdl_error(NULL, errno);
	pid = fork();
	if (pid == 0)
		ft_tipeu1(av, env, pipefd);
	pid = fork();
	if (pid == 0)
		ft_tipeu2(av, env, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	check_exit();
	return (0);
}
