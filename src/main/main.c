/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:06:11 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:06:15 by root             ###   ########.fr       */
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
		init_signal();
		rl_done = 0;
		g_signal = 0;
		line = readline(PROMPT);
		if (g_signal == SIGINT)
		{
			data->last_status = 130;
			g_signal = 0;
		}
		if (!line)
			return (data->last_status);
		else if (line[0] != '\0' && hdl_args(data, line) == 1)
			continue ;
		if (line)
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
	int		last_status;

	data = NULL;
	(void)ac;
	(void)av;
	data = init(envp);
	if (!data)
		return (1);
	g_signal = 0;
	last_status = loop(data);
	free_data(data);
	rl_clear_history();
	ft_fprintf(STDOUT_FILENO, "exit\n");
	return (last_status);
}
