/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:14 by root              #+#    #+#             */
/*   Updated: 2026/03/20 03:59:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		EXEC_H
# define	EXEC_H

# include "minishell.h"
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_env	t_env;

int		exec(t_cmd *cmd_tabl, t_shell *data);
// void	exec_ult(int ac, char **av, t_env *env);
void	free_cmd_list(t_cmd *cmd_list);
char	**env_to_tab(t_env *envp);
void	exec_cmd(char **args, t_env *env);
char	*get_path(char *cmd, t_env *env);
char	**get_path_list(t_env *env);
void	hdl_error(char *arg, int err_code);

#endif