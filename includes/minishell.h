/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzidani <yzidani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:30 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 17:47:56 by yzidani          ###   ########.fr       */
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

// Token types
# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_REDIR_APPEND 4
# define TOKEN_HERE_DOC 5

typedef struct s_shell
{
	int		pid;
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
	struct s_cmd	*next;
}				t_cmd;

// Parsing
t_cmd	*parsing(t_shell *shell);
t_token	*tokenize(t_shell *shell);
void	free_tokens(t_token *token_list);

// Token Utils
t_token	*create_token(char *value, int type);
void	add_token(t_token **list, t_token *new_token);
int		get_token_type(const char *str);
int		get_word_len(const char *str, int i);
int		is_operator(char c);

#endif