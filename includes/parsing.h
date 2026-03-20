/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:31:24 by root              #+#    #+#             */
/*   Updated: 2026/03/19 17:13:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// Token types
# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HERE_DOC 5

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

// Parsing
t_cmd	*parsing(t_shell *shell);
t_token	*tokenize(t_shell *shell);
t_cmd	*parse_tokens(t_token *token_list);
void	free_tokens(t_token *token_list);
void	expand(t_cmd *cmd_list, t_shell *shell);
char	*expand_word(const char *src, t_shell *shell);
char	**expand_av(char **av, t_shell *shell);
char	*exp_append_char(char *src, char c);
char	*exp_append_str(char *src, const char *add);
char	*exp_get_env_value(t_shell *shell, const char *key);
char	*remove_quotes(char *str);
int		has_unclosed_quote(const char *str);
int		skip_quotes(const char *str, int i, char quote);
t_cmd	*init_cmd(void);
int		is_redir(int type);
void	handle_redir(t_cmd *cmd, t_token **tok);
int		count_args(t_token *start, t_token *end);
char	**build_args(t_token *start, t_token *end);

// Token Utils
t_token	*create_token(char *value, int type);
void	add_token(t_token **list, t_token *new_token);
int		get_token_type(const char *str);
int		get_word_len(const char *str, int i);
int		is_operator(char c);

#endif