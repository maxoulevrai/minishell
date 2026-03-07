/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:16:33 by yzidani           #+#    #+#             */
/*   Updated: 2026/03/07 16:17:15 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_av(char **av, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (av && av[i])
	{
		expanded = expand_word(av[i], shell);
		if (!expanded)
			return (av);
		free(av[i]);
		av[i] = expanded;
		i++;
	}
	return (av);
}
