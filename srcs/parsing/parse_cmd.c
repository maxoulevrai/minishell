/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:16:07 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/07 16:17:26 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*parse_single_cmd(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	tmp = start;
	while (tmp && tmp != end)
	{
		if (is_redir(tmp->type))
			handle_redir(cmd, &tmp);
		else
			tmp = tmp->next;
	}
	cmd->args = build_args(start, end);
	return (cmd);
}

static void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*start;
	t_token	*tmp;

	if (!tokens)
		return (NULL);
	head = NULL;
	start = tokens;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE || !tmp->next)
		{
			current = parse_single_cmd(start, tmp->type == PIPE ? tmp : NULL);
			if (!current)
				return (NULL);
			add_cmd_to_list(&head, current);
			start = tmp->next;
		}
		tmp = tmp->next;
	}
	return (head);
}
