/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:08:04 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:08:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_redirection(char **file_ptr, t_shell *shell)
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
		expand_cmd_redirs(command, shell);
		update_redirection(&command->input_file, shell);
		update_redirection(&command->output_file, shell);
		command = command->next;
	}
}
