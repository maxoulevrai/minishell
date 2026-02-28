/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 17:29:58 by yzidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "6ft shell>>"

typedef struct s_shell
{
	int		pid;
	t_env	*envp;
}				t_shell;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		id;
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
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char	*line;
	t_env	*envp;
}				t_data;

// Parsing
t_cmd	*parsing(t_data *data);

#endif