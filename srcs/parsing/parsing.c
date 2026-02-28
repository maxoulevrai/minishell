/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:01:13 by yzidani           #+#    #+#             */
/*   Updated: 2026/02/28 17:34:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsing(t_data *data)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = tokenize(data);
	if (!token_list)
		return (NULL);
	cmd_list = parse_tokens(token_list);
	free_tokens(token_list);
	return (cmd_list);
}
