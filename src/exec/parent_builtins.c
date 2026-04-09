/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:07:00 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:07:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	hdl_failed_redir(t_shell *data)
{
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	close(data->save_in);
	close(data->save_out);
	if (g_signal == SIGINT)
	{
		data->last_status = 130;
		g_signal = 0;
		return (130);
	}
	return (1);
}

static int	run_parent_builtin(t_cmd *cmd, t_shell *data)
{
	int	status;

	if (apply_redirs(cmd) == -1)
		return (hdl_failed_redir(data));
	status = builtins_dispatcher(data, cmd);
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	close(data->save_in);
	close(data->save_out);
	data->last_status = status;
	return (status);
}

int	exec_parent_builtin(t_cmd *cmd, t_shell *data)
{
	data->save_in = dup(STDIN_FILENO);
	data->save_out = dup(STDOUT_FILENO);
	if (data->save_in == -1 || data->save_out == -1)
	{
		if (data->save_in != -1)
			close(data->save_in);
		if (data->save_out != -1)
			close(data->save_out);
		return (1);
	}
	return (run_parent_builtin(cmd, data));
}
