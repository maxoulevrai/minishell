/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:57:21 by maleca             #+#    #+#             */
/*   Updated: 2026/03/20 18:41:09 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_key(char *env_line)
{
	int		i;
	char	*ret;
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	ret = ft_strndup(env_line, i);
	return (ret);
}

char	*get_env_value(char *env_line)
{
	int		i;
	char	*ret;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	ret = ft_strdup(&env_line[i + 1]);
	return (ret);
}

char	*get_env(t_env **envp, char *key)
{
	t_env	*tmp;

	if (!envp || !*envp || !key)
		return (NULL);
	tmp = *envp;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
