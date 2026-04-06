/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:36:48 by root              #+#    #+#             */
/*   Updated: 2026/03/26 17:37:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*next;

	while (cmd_list)
	{
		next = cmd_list->next;
		if (cmd_list->args)
			free_dtab(cmd_list->args);
		if (cmd_list->heredoc && cmd_list->heredoc_fd > STDERR_FILENO)
			close(cmd_list->heredoc_fd);
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list);
		cmd_list = next;
	}
}
