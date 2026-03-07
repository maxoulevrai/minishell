/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:16:13 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/07 16:17:20 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	next_quote_state(int quote, char c)
{
	if (c == '\'' && quote != 2)
	{
		if (quote == 1)
			return (0);
		return (1);
	}
	if (c == '"' && quote != 1)
	{
		if (quote == 2)
			return (0);
		return (2);
	}
	return (quote);
}

static char	*expand_var(const char *src, int *i, t_shell *shell)
{
	int		start;
	char	*name;
	char	*value;

	if (src[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(shell->last_status));
	}
	if (!ft_isalpha(src[*i + 1]) && src[*i + 1] != '_')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	start = ++(*i);
	while (src[*i] && is_var_char(src[*i]))
		(*i)++;
	name = ft_substr(src, start, *i - start);
	if (!name)
		return (NULL);
	value = exp_get_env_value(shell, name);
	free(name);
	return (value);
}

static char	*expand_loop(const char *src, t_shell *shell, char *out)
{
	char	*val;
	int		i;
	int		q;
	int		next;

	i = 0;
	q = 0;
	while (out && src && src[i])
	{
		next = next_quote_state(q, src[i]);
		if (next != q)
			q = next;
		else if (src[i] == '$' && q != 1)
		{
			val = expand_var(src, &i, shell);
			out = exp_append_str(out, val);
			free(val);
			continue ;
		}
		else
			out = exp_append_char(out, src[i]);
		i++;
	}
	return (out);
}

char	*expand_word(const char *src, t_shell *shell)
{
	char	*out;

	out = ft_strdup("");
	return (expand_loop(src, shell, out));
}
