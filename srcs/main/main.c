/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/03/17 18:07:19 by root             ###   ########.fr       */
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
	t_cmd	*cmd_tabl;

	while (1)
	{
		data->line = readline(PROMPT);
		if (!data->line) // == EOF (Ctrl + D)
			return (EXIT_FAILURE);
		else if (data->line[0] != '\0')
		{
			add_history(data->line);
			cmd_tabl = parsing(data);
			if (!cmd_tabl)
			{
				free(data->line);
				continue ;
			}
			exec(cmd_tabl, data);
			free_cmd_list(cmd_tabl);
		}
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
	if (!data)
		return (1);
	loop(data);
	return (0);
}

