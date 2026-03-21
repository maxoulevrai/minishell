#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_signal(int sig)
{
	g_signal = sig;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	check_signal(t_shell *data)
{
	if (g_signal == SIGINT)
	{
		data->last_status = 130;
		g_signal = 0;
		return (1);
	}
	if (g_signal == SIGQUIT)
	{
		g_signal = 0;
		return (1);
	}
	return (0);
}
