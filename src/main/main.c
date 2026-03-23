/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca<maleca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:53:41 by maleca            #+#    #+#             */
/*   Updated: 2026/03/23 14:46:15 by maleca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

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
	return (data);
}

static int	hdl_args(t_shell *data, char *line)
{
	t_cmd	*cmd_tabl;

	add_history(line);
	cmd_tabl = parsing(line, data);
	if (!cmd_tabl)
	{
		free(line);
		return (1);
	}
	exec(cmd_tabl, data);
	free_cmd_list(cmd_tabl);
	return (0);
}

static int	loop(t_shell *data)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (g_signal == SIGINT)
		{
			data->last_status = 130;
			g_signal = 0;
			free(line);
			continue ;
		}
		if (!line)
			return (EXIT_FAILURE);
		else if (line[0] != '\0' && hdl_args(data, line) == 1)
			continue ;
		free(line);
	}
	return (EXIT_SUCCESS);
}

void	free_data(t_shell *data)
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
	g_signal = 0;
	init_signal();
	loop(data);
	free_data(data);
	ft_fprintf(STDOUT_FILENO, "exit\n");
	return (0);
}
