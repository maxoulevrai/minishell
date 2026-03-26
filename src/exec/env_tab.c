/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:37:03 by root              #+#    #+#             */
/*   Updated: 2026/03/26 17:37:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	env_len(t_env *envp)
{
	int	len;

	len = 0;
	while (envp && ++len)
		envp = envp->next;
	return (len);
}

char	**env_to_tab(t_env *envp)
{
	char	**env;
	char	*tmp;
	int		i;

	env = ft_calloc(env_len(envp) + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp)
	{
		tmp = ft_strjoin(envp->key, "=");
		if (!tmp)
			return (free_dtab(env), NULL);
		env[i] = ft_strdup(tmp);
		if (envp->value)
			env[i] = (free(env[i]), ft_strjoin(tmp, envp->value));
		free(tmp);
		if (!env[i])
			return (free_dtab(env), NULL);
		i++;
		envp = envp->next;
	}
	return (env);
}
