/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinss.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:41:35 by root              #+#    #+#             */
/*   Updated: 2026/03/18 18:00:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../lib/includes/libft.h"
# include "../lib/includes/ft_printf.h"
# include "../lib/includes/ft_fprintf.h"
# include "../lib/includes/get_next_line.h"
# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;
typedef struct s_env	t_env;

# define TRUE 1
# define FALSE 0

int	builtins_checker(char *arg);
int	builtins_dispatcher(t_env *envp, char **args);
int	ft_cd(t_env *envp, char **args);
int	ft_echo(char **args);
int	ft_env(t_env *envp, char **cmd);
int	ft_exit(char **cmd);
int	ft_export(t_env *envp, char **args);
int	ft_pwd(void);
int	ft_unset(t_env *envp, char **args);


#endif
