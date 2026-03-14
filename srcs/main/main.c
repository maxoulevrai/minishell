/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/03/14 18:39:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


t_shell	*init(char **envp)
{
	t_shell	*data;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->envp = env_dup(envp);
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	data->last_status = 0;
	data->pid_table  = NULL;
	data->line = NULL;
	return (data);
}

int	loop(t_shell *data)
{

	while (1)
	{
		data->line = readline(PROMPT);
		if (!data->line) // == EOF (Ctrl + D)
			return (EXIT_FAILURE);
		else if (data->line[0] != '\0')
			add_history(data->line);
		ft_fprintf(STDOUT_FILENO, "oeoeo: %s\n", data->line);
		free(data->line);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*data;

	data = NULL;
	(void)ac;
	(void)av;
	data = init(envp);
	data->envp = env_dup(envp);
	loop(data);
	return (0);
}

