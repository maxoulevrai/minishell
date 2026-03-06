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

static void	expand_redirs(t_cmd *cmd, t_shell *shell)
{
	char	*expanded;

	if (cmd->input_file)
	{
		expanded = expand_word(cmd->input_file, shell);
		if (expanded)
			free(cmd->input_file);
		cmd->input_file = expanded;
	}
	if (cmd->output_file)
	{
		expanded = expand_word(cmd->output_file, shell);
		if (expanded)
			free(cmd->output_file);
		cmd->output_file = expanded;
	}
}

void	expand(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*cur;

	cur = cmd_list;
	while (cur)
	{
		if (cur->args)
			cur->args = expand_argv(cur->args, shell);
		expand_redirs(cur, shell);
		cur = cur->next;
	}
}
