/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:38:19 by root              #+#    #+#             */
/*   Updated: 2026/03/27 17:31:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_parent_builtin(t_cmd *cmd, t_shell *data)
{
	int	status;

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
	if (apply_input_redir(cmd) == -1 || apply_output_redir(cmd) == -1)
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
	status = builtins_dispatcher(data, cmd);
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
	close(data->save_in);
	close(data->save_out);
	data->last_status = status;
	return (status);
}
