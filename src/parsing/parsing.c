/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:01:13 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/21 16:07:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsing(const char *line, t_shell *shell)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = tokenize(line);
	if (!token_list)
		return (NULL);
	cmd_list = parse_tokens(token_list);
	free_tokens(token_list);
	if (cmd_list)
		expand(cmd_list, shell);
	return (cmd_list);
}
