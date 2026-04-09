/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:08:17 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:08:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	report_syntax_error(char *token)
{
	if (!token)
		ft_fprintf(STDERR_FILENO,
			"6ft shell: syntax error near unexpected token `newline'\n");
	else
		ft_fprintf(STDERR_FILENO,
			"6ft shell: syntax error near unexpected token `%s'\n", token);
	return (1);
}

static int	validate_syntax(t_token *tokens)
{
	t_token	*cur;

	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
		return (report_syntax_error("|"));
	cur = tokens;
	while (cur)
	{
		if (cur->type == PIPE && (!cur->next || cur->next->type == PIPE))
			return (report_syntax_error("|"));
		if (is_redir(cur->type))
		{
			if (!cur->next)
				return (report_syntax_error(NULL));
			if (cur->next->type != WORD)
				return (report_syntax_error(cur->next->value));
		}
		cur = cur->next;
	}
	return (0);
}

t_cmd	*parsing(const char *line, t_shell *shell)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	if (has_unclosed_quote(line))
	{
		shell->last_status = 2;
		ft_fprintf(STDERR_FILENO,
			"6ft shell: syntax error: unclosed quote\n");
		return (NULL);
	}
	token_list = tokenize(line);
	if (!token_list)
		return (shell->last_status = 2, NULL);
	if (validate_syntax(token_list))
	{
		shell->last_status = 2;
		return (free_tokens(token_list), NULL);
	}
	cmd_list = parse_tokens(token_list);
	free_tokens(token_list);
	if (cmd_list)
		expand(cmd_list, shell);
	else
		shell->last_status = 1;
	return (cmd_list);
}
