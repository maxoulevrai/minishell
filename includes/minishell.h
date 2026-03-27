/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:47:30 by root              #+#    #+#             */
/*   Updated: 2026/03/27 16:23:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\001\033[1;36m\0026ft shell> \001\033[0m\002"

extern volatile sig_atomic_t	g_signal;

typedef struct s_env			t_env;

typedef struct s_shell
{
	t_env	*envp;
	int		save_in;
	int		save_out;
	int		last_status;
}				t_shell;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}				t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}				t_cmd;

//		-- ENV --
int		main(int ac, char **av, char **envp);
void	ft_envadd_back(t_env **head, t_env *new);
void	set_env_var(t_env **envp, char *key, char *value);
t_env	*env_dup(char **envp);
t_env	*init_env_node(char	*env_line);
char	*get_env_value(char *env_line);
char	*get_env_key(char *env_line);
char	*get_env(t_env **envp, char *key);

//		-- SIGNALS --

void	init_signal(void);
void	set_signal_heredoc(void);
void	set_signal_exec_parent(void);
void	set_signal_exec_child(void);

//		-- MEM --

void	free_data(t_shell *data);

#endif