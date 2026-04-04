/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:47:49 by root              #+#    #+#             */
/*   Updated: 2026/04/04 16:21:30 by root             ###   ########.fr       */
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
void	free_cmd_list(t_cmd *cmd_list);
char	**env_to_tab(t_env *envp);
void	exec_cmd(t_cmd *cmd, t_shell *data);
char	*get_path(char *cmd, t_env *env);
char	**get_path_list(t_env *env);
int		is_parent_builtin(char *cmd);
int		exec_parent_builtin(t_cmd *cmd, t_shell *data);
int		apply_input_redir(t_cmd *cmd);
int		apply_output_redir(t_cmd *cmd);
int		heredoc_to_fd(char *limiter);
void	hdl_error(t_shell *data, t_cmd *cmd_tbl, char *arg, int err_code);

#endif