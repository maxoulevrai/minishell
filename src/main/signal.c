/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:39:25 by maleca            #+#    #+#             */
/*   Updated: 2026/03/30 17:03:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	hdl_signal(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
}

static void	hdl_signal_parent(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	rl_done = 1;
}

// void	exit_on_sigint(t_shell *data)
// {
// 	if (g_signal == SIGINT)
// 	{
// 		data->last_status = 130;
// 		g_signal = 0;
// 	}
// }

void	init_signal(void)
{
	g_signal = 0;
	signal(SIGINT, hdl_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_exec_parent(void)
{
	signal(SIGINT, hdl_signal_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
