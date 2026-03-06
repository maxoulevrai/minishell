/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 10:00:00 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/06 10:00:00 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_argv(char **argv, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv && argv[i])
	{
		expanded = expand_word(argv[i], shell);
		if (!expanded)
			return (argv);
		free(argv[i]);
		argv[i] = expanded;
		i++;
	}
	return (argv);
}
