/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2026/03/20 19:09:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
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
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "6ft shell>> $ "

typedef struct s_env	t_env;

typedef struct s_shell
{
	pid_t	*pid_table;
	int		last_status;
	char	*line;
	t_env	*envp;
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

int		main(int ac, char **av, char **envp);
t_env	*env_dup(char **envp);
void	ft_envadd_back(t_env **head, t_env *new);
t_env	*init_env_node(char	*env_line);
char	*get_env_value(char *env_line);
char	*get_env_key(char *env_line) ;
char	*get_env(t_env **envp, char *key);


#endif