/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:39:51 by maleca            #+#    #+#             */
/*   Updated: 2026/02/24 14:53:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../lib/includes/libft.h"
# include <errno.h>

void	check_exit(void);
void	exec_cmd(char *cmd, char **env);
void	hdl_error(char *arg, int err_code);
void	exec_ult(int ac, char **av, char **env);
char	**get_path_list(char **env);
char	*get_path(char *cmd, char **env);

#endif