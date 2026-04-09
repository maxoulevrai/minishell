/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:06:41 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:06:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	hdl_redir_error(t_cmd *cmd_head, t_shell *data)
{
	if (g_signal == SIGINT)
		_exit(130);
	free_cmd_list(cmd_head);
	free_data(data);
	ft_fprintf(STDERR_FILENO, "6ft shell: redir: %s\n", strerror(errno));
	_exit(1);
}
