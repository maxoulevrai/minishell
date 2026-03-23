/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:30:00 by maleca             #+#    #+#             */
/*   Updated: 2026/03/20 18:21:00 by maleca            ###   ########.fr       */
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
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list);
		cmd_list = next;
	}
}
