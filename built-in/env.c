/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:23:44 by root              #+#    #+#             */
/*   Updated: 2026/03/05 01:25:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"






// env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]

int	ft_env(t_env *envp, char **cmd)
{
	t_env	*tmp;

	tmp  = envp;
	if (cmd[1])
		return (127);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->value)
			ft_fprintf(1, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}