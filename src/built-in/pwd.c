/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:10:06 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:10:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// commande pwd 
// prototype: pwd [OPTION]

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_fprintf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
