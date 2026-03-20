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

static int	update_quote_state(int current_state, char ch)
{
	if (ch == '\'' && current_state != 2)
	{
		if (current_state == 1)
			return (0);
		return (1);
	}
	if (ch == '"' && current_state != 1)
	{
		if (current_state == 2)
			return (0);
		return (2);
	}
	return (current_state);
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
	int		j;
	int		next;

	i = 0;
	j = 0;
	while (out && src && src[i])
	{
		next = update_quote_state(j, src[i]);
		if (next != j)
			j = next;
		else if (src[i] == '$' && j != 1)
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
