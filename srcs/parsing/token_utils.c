/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/04 10:00:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **list, t_token *new_token)
{
	t_token	*current;

	if (!list || !new_token)
		return ;
	if (!*list)
	{
		*list = new_token;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	get_token_type(const char *str)
{
	if (!str || !*str)
		return (WORD);
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(str, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(str, "<<") == 0)
		return (HERE_DOC);
	return (WORD);
}

int	get_word_len(const char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '|'
		&& str[i] != '<' && str[i] != '>')
	{
		len++;
		i++;
	}
	return (len);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
