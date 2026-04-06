/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:39:25 by maleca            #+#    #+#             */
/*   Updated: 2026/04/06 18:46:31 by root             ###   ########.fr       */
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

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static int	heredoc_event_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	init_signal(void)
{
	signal(SIGINT, hdl_signal);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = NULL;
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = heredoc_event_hook;
}
