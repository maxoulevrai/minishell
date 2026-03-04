/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:14:48 by yzidani           #+#    #+#             */
/*   Updated: 2026/02/28 17:29:58 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_operator(const char *line, int *i)
{
	char	*op;

	op = NULL;
	if (line[*i] == '|' && ++(*i))
		op = ft_strdup("|");
	else if (line[*i] == '>' && line[*i + 1] == '>' && (*i += 2))
		op = ft_strdup(">>");
	else if (line[*i] == '>' && ++(*i))
		op = ft_strdup(">");
	else if (line[*i] == '<' && line[*i + 1] == '<' && (*i += 2))
		op = ft_strdup("<<");
	else if (line[*i] == '<' && ++(*i))
		op = ft_strdup("<");
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

t_token	*tokenize(t_shell *shell)
{
	t_token	*token_list;
	int		i;

	if (!shell || !shell->line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (shell->line[i])
	{
		while (ft_isspace(shell->line[i]))
			i++;
		if (!shell->line[i])
			break ;
		if (!process_token(&token_list, shell->line, &i))
			return (free_tokens(token_list), NULL);
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
