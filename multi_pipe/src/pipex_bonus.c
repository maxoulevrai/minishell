/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2026/02/05 19:07:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	here_doc_child(int pipefd[2], char *LIMITER)
{
	char	*line;
	char	*limiter_nl;

	limiter_nl = ft_strjoin(LIMITER, "\n");
	close(pipefd[0]);
	line = get_next_line(STDIN_FILENO, limiter_nl);
	while (line)
	{
		if (ft_strcmp(line, limiter_nl) == 0)
		{
			close(pipefd[1]);
			free(limiter_nl);
			free(line);
			_exit(EXIT_SUCCESS);
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, limiter_nl);
	}
	close(pipefd[1]);
	free(limiter_nl);
	free(line);
	_exit(EXIT_SUCCESS);
}

static void	hdl_here_doc(char *LIMITER, int ac)
{
	pid_t	pid;
	int		pipefd[2];

	if (ac < 6)
	{
		ft_fprintf(STDERR_FILENO, "too few arguments\n");
		_exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
		hdl_error(NULL, errno);
	pid = fork();
	if (pid == -1)
		hdl_error(NULL, errno);
	if (pid == 0)
		here_doc_child(pipefd, LIMITER);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

static void	ft_tipeu(char *av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		hdl_error(NULL, errno);
	pid = fork();
	if (pid == -1)
		hdl_error(NULL, errno);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_cmd(av, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

static void	ult_cmd(int ac, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		hdl_error(NULL, errno);
	if (pid == 0)
		exec_ult(ac, av, env);
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	infile;

	if (ac < 5)
		return (ft_fprintf(STDERR_FILENO, "too few arguments\n"), EXIT_FAILURE);
	errno = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		hdl_here_doc(av[2], ac);
		i = 3;
	}
	else
	{
		i = 2;
		infile = open(av[1], O_RDONLY, 0644);
		if (infile == -1)
			hdl_error(av[1], errno);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	while (i < ac - 2)
		ft_tipeu(av[i++], env);
	ult_cmd(ac, av, env);
	check_exit();
	return (0);
}
