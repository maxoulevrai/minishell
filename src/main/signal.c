/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:39:25 by maleca             #+#    #+#             */
/*   Updated: 2026/03/23 14:46:52 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	hdl_signal_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

static void	hdl_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

void	init_signal(void)
{
	g_signal = 0;
	signal(SIGINT, hdl_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, hdl_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_exec_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
