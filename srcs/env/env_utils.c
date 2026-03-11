/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:57:21 by root              #+#    #+#             */
/*   Updated: 2026/03/07 19:28:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*get_env(t_env **envp, char *key)
{
	size_t	i;
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (tmp->key == key)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
