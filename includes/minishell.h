/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2026/03/23 14:56:41 by root             ###   ########.fr       */
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
t_env	*env_dup(char **envp);
void	ft_envadd_back(t_env **head, t_env *new);
t_env	*init_env_node(char	*env_line);
char	*get_env_value(char *env_line);
char	*get_env_key(char *env_line);
char	*get_env(t_env **envp, char *key);

//		-- SIGNALS --

void	init_signal(void);
void	set_signal_heredoc(void);

#endif