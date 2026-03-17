/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:15:55 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/07 16:17:32 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_quotes(const char *str, int i, char quote)
{
	int	len;

	len = 1;
	i++;
	while (str[i] && str[i] != quote)
	{
		len++;
		i++;
	}
	if (str[i] == quote)
		len++;
	return (len);
}

static char	*build_unquoted(const char *src)
{
	char	*result;
	int		src_idx;
	int		dst_idx;
	char	quote;

	result = malloc(ft_strlen(src) + 1);
	if (!result)
		return (NULL);
	src_idx = 0;
	dst_idx = 0;
	while (src[src_idx])
	{
		quote = 0;
		if (src[src_idx] == '\'' || src[src_idx] == '"')
			quote = src[src_idx++];
		while (src[src_idx] && src[src_idx] != quote && quote != 0)
			result[dst_idx++] = src[src_idx++];
		if (quote && src[src_idx] == quote)
			src_idx++;
		if (!quote)
			result[dst_idx++] = src[src_idx++];
	}
	result[dst_idx] = '\0';
	return (result);
}

char	*remove_quotes(char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	new = build_unquoted(str);
	free(str);
	return (new);
}

int	has_unclosed_quote(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}
