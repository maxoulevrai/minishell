/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:47:49 by root              #+#    #+#             */
/*   Updated: 2026/04/06 19:48:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

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
int		wait_pipeline(pid_t last_pid);
int		is_parent_builtin(char *cmd);
int		exec_parent_builtin(t_cmd *cmd, t_shell *data);
int		apply_redirs(t_cmd *cmd);
int		heredoc_to_fd(char *limiter);
char	**env_to_tab(t_env *envp);
char	*get_path(char *cmd, t_env *env);
char	**get_path_list(t_env *env);
void	free_cmd_list(t_cmd *cmd_list);
void	exec_cmd(t_cmd *cmd, t_shell *data);
void	hdl_error(t_shell *data, t_cmd *cmd_tbl, char *arg, int err_code);
void	hdl_redir_error(t_cmd *cur, t_shell *data);
void	child_process(t_cmd *cur, t_shell *data, int prev_read, int pipefd[2]);

#endif