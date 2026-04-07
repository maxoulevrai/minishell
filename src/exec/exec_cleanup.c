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

static void	free_redirs(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		free(cmd->redir_files[i]);
		i++;
	}
	free(cmd->redir_types);
	free(cmd->redir_files);
}

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
		free_redirs(cmd_list);
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list);
		cmd_list = next;
	}
}
