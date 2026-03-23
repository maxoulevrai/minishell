/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:14:48 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/21 16:07:49 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_operator(const char *line, int *i)
{
	char	*op;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		return (ft_strdup(">>"));
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i += 2;
		return (ft_strdup("<<"));
	}
	if (line[*i] == '>')
		op = ft_strdup(">");
	else if (line[*i] == '<')
		op = ft_strdup("<");
	else if (line[*i] == '|')
		op = ft_strdup("|");
	else
		return (NULL);
	(*i)++;
	return (op);
}

static char	*extract_word(const char *line, int *i)
{
	int		start;
	int		word_len;
	char	*word;

	start = *i;
	word_len = get_word_len(line, start);
	word = ft_substr(line, start, word_len);
	*i += word_len;
	return (word);
}

static int	process_token(t_token **list, const char *line, int *i)
{
	char	*token_value;
	t_token	*new_token;

	if (is_operator(line[*i]))
		token_value = extract_operator(line, i);
	else
		token_value = extract_word(line, i);
	if (!token_value)
		return (0);
	new_token = create_token(token_value, get_token_type(token_value));
	if (!new_token)
	{
		free(token_value);
		return (0);
	}
	add_token(list, new_token);
	return (1);
}

t_token	*tokenize(const char *line)
{
	t_token	*token_list;
	int		i;

	if (!line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' '
				|| line[i] == '\t' || line[i] == '\n'))
			i++;
		if (!line[i])
			break ;
		if (!process_token(&token_list, line, &i))
		{
			free_tokens(token_list);
			return (NULL);
		}
	}
	return (token_list);
}

void	free_tokens(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}
