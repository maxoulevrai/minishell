/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:02:23 by root              #+#    #+#             */
/*   Updated: 2026/02/24 17:07:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"

// commande cd
// prototype: cd [path]
// sans argument -> va dans HOME
// avec argument -> va dans le path donné

int	ft_cd(char **t_cmd)
{
	char	*path;
	char	*home;

	if (!t_cmd[1])
	{
		home = get_env("HOME");
		if (!home)
			return (ft_fprintf(STDERR_FILENO, "cd: HOME not set\n"), 1);
		path = home;
	}
	else if (t_cmd[2])
		return (ft_fprintf(STDERR_FILENO, "cd: too many arguments\n"), 1);
	else
		path = t_cmd[1];
	if (chdir(path) == -1)
	{
		ft_fprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
