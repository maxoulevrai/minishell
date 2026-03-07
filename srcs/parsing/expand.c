/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:14:46 by yzidani           #+#    #+#             */
/*   Updated: 2026/02/28 17:29:58 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_redirection(t_cmd *command, char **file_ptr, t_shell *shell)
{
	char	*result;

	if (*file_ptr)
	{
		result = expand_word(*file_ptr, shell);
		if (result)
		{
			free(*file_ptr);
			*file_ptr = result;
		}
	}
}

void	expand(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*command;

	command = cmd_list;
	while (command)
	{
		if (command->args)
			command->args = expand_av(command->args, shell);
		update_redirection(command, &command->input_file, shell);
		update_redirection(command, &command->output_file, shell);
		command = command->next;
	}
}
