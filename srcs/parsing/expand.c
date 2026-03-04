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

void	expand(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (current->args)
			current->args = expand_args(current->args, shell);
		if (current->input_file)
			current->input_file = expand_args(current->input_file, shell);
		if (current->output_file)
			current->output_file = expand_args(current->output_file, shell);
		current = current->next;
	}
}
