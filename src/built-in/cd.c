/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:02:23 by maleca             #+#    #+#             */
/*   Updated: 2026/03/23 16:12:59 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// commande cd
// prototype: cd [path]
// sans argument -> va dans HOME
// avec argument -> va dans le path donné

char	*get_env(t_env **envp, char *key);

int	ft_cd(t_env *envp, char **t_cmd)
{
	char	*path;
	char	*home;

	if (!t_cmd[1])
	{
		home = get_env(&envp, "HOME");
		if (!home)
			return (ft_fprintf(STDERR_FILENO,
					"minishell: cd: HOME not set\n"), 1);
		path = home;
	}
	else if (t_cmd[2])
		return (ft_fprintf(STDERR_FILENO,
				"minishell: cd: too many arguments\n"), 1);
	else
		path = t_cmd[1];
	if (chdir(path) == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n",
			path, strerror(errno));
		return (1);
	}
	return (0);
}
