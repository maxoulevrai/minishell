/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:16:26 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/07 16:17:18 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*exp_append_char(char *src, char c)
{
	char	*new;
	size_t	len;

	if (!src)
		src = ft_strdup("");
	len = ft_strlen(src);
	new = malloc(len + 2);
	if (!new)
		return (free(src), NULL);
	ft_memcpy(new, src, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(src);
	return (new);
}

char	*exp_append_str(char *src, const char *add)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!src)
		src = ft_strdup("");
	if (!add)
		add = "";
	len1 = ft_strlen(src);
	len2 = ft_strlen(add);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (free(src), NULL);
	ft_memcpy(new, src, len1);
	ft_memcpy(new + len1, add, len2 + 1);
	free(src);
	return (new);
}

char	*exp_get_env_value(t_shell *shell, const char *key)
{
	t_env	*cur;

	cur = shell->envp;
	while (cur)
	{
		if (cur->key && ft_strcmp(cur->key, (char *)key) == 0)
			return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (ft_strdup(""));
}
