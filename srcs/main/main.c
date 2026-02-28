/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 17:50:37 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	**env_cpy;


	init();
	env_cpy = save_env(envp);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)

		lexer
		parse
		exec
		free(line);
	}
}
