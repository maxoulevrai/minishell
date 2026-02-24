/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:30:03 by root              #+#    #+#             */
/*   Updated: 2026/02/24 16:45:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"

// commande pwd 
// prototype: pwd [OPTION]

int	ft_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: error retrieving current directory");
		return (1);
	}
	ft_fprintf(1, "%s\n", cwd);
	return (0);
}
