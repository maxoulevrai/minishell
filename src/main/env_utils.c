/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:47:03 by root              #+#    #+#             */
/*   Updated: 2026/03/26 17:47:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_key(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	return (ft_strndup(env_line, i));
}

char	*get_env_value(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (!env_line[i])
		return (NULL);
	return (ft_strdup(&env_line[i + 1]));
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
