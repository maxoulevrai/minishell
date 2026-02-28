/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:01:13 by yzidani           #+#    #+#             */
/*   Updated: 2026/02/28 17:49:16 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsing(t_shell *shell)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = tokenize(shell);
	if (!token_list)
		return (NULL);
	cmd_list = parse_tokens(token_list);
	free_tokens(token_list);
	return (cmd_list);
}
