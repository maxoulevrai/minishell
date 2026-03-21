/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/03/20 04:30:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_shell	*init(char **envp)
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
	data->pid_table = NULL;
	data->line = NULL;
	setup_signals();
	return (data);
}

static int	loop(t_shell *data)
{
	t_cmd	*cmd_tabl;

	while (1)
	{
		data->line = readline(PROMPT);
		if (!data->line) // == EOF (Ctrl + D)
			return (EXIT_FAILURE);
		if (!check_signal(data) && data->line[0] != '\0')
		{
			add_history(data->line);
			cmd_tabl = parsing(data);
			if (cmd_tabl)
			{
				exec(cmd_tabl, data);
				free_cmd_list(cmd_tabl);
			}
		}
		free(data->line);
	}
	return (EXIT_SUCCESS);
}

void	free_all(t_shell *data)
{
	t_env	*cur;
	t_env	*next;

	if (!data)
		return ;
	cur = data->envp;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	free(data->line);
	free(data);
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
	free_all(data);
	return (0);
}

