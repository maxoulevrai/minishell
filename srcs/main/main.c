/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 17:48:58 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**save_env(char **envp)
{
	int	i;
	char **env_cpy;

	i = 0;
	while (envp[i])
		i++;
	env_cpy = malloc(sizeof(char *) + (i + 1));
	if (!env_cpy)
		return (NULL);
	while (i >= 0)
	{
		env_cpy[i] = ft_strdup(envp[i]);
		if (!env_cpy[i])
			return (free_all(), NULL);
		i--;
	}
	return (env_cpy);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	**env_cpy;


	init();
	env_cpy = save_env(envp);
	while (1)
	{
		shell.line = readline(PROMPT);
		
	}
}