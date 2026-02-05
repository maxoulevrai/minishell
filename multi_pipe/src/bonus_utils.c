/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 19:58:14 by maleca            #+#    #+#             */
/*   Updated: 2025/09/16 16:55:52 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_ult(int ac, char **av, char **env)
{
	int	outfile;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			hdl_error(av[ac - 1], errno);
	}
	else
	{
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			hdl_error(av[ac - 1], errno);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec_cmd(av[ac - 2], env);
}
