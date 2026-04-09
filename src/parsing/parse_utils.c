/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:09:41 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:09:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_fd = 0;
	cmd->redir_count = 0;
	cmd->redir_types = NULL;
	cmd->redir_files = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HERE_DOC);
}

void	handle_redir(t_cmd *cmd, t_token **tok)
{
	int	type;

	type = (*tok)->type;
	*tok = (*tok)->next;
	if (!*tok || (*tok)->type != WORD)
		return ;
	if (add_cmd_redir(cmd, type, (*tok)->value) != 0)
		return ;
	set_effective_redir(cmd, type, (*tok)->value);
	*tok = (*tok)->next;
}

int	count_args(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = start;
	while (tmp && tmp != end)
	{
		if (tmp->type == WORD)
			count++;
		else if (is_redir(tmp->type) && tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}

char	**build_args(t_token *start, t_token *end)
{
	char	**args;
	int		count;
	int		i;

	count = count_args(start, end);
	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (start && start != end && i < count)
	{
		if (start->type == WORD)
			args[i++] = ft_strdup(start->value);
		else if (is_redir(start->type) && start->next)
			start = start->next;
		start = start->next;
	}
	return (args);
}
