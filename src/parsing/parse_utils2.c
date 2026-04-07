/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by root              #+#    #+#             */
/*   Updated: 2026/04/07 00:00:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	grow_redirs(t_cmd *cmd, int **types, char ***files)
{
	int	i;

	*types = ft_calloc(cmd->redir_count + 1, sizeof(int));
	*files = ft_calloc(cmd->redir_count + 1, sizeof(char *));
	if (!*types || !*files)
		return (free(*types), free(*files), 1);
	i = 0;
	while (i < cmd->redir_count)
	{
		(*types)[i] = cmd->redir_types[i];
		(*files)[i] = cmd->redir_files[i];
		i++;
	}
	return (0);
}

int	add_cmd_redir(t_cmd *cmd, int type, const char *value)
{
	int		*new_types;
	char	**new_files;
	int		i;

	if (grow_redirs(cmd, &new_types, &new_files) != 0)
		return (1);
	i = cmd->redir_count;
	new_types[i] = type;
	new_files[i] = ft_strdup(value);
	if (!new_files[i])
		return (free(new_types), free(new_files), 1);
	free(cmd->redir_types);
	free(cmd->redir_files);
	cmd->redir_types = new_types;
	cmd->redir_files = new_files;
	cmd->redir_count++;
	return (0);
}

void	set_effective_redir(t_cmd *cmd, int type, const char *value)
{
	if (type == REDIR_IN || type == HERE_DOC)
	{
		free(cmd->input_file);
		cmd->input_file = ft_strdup(value);
		if (type == HERE_DOC)
			cmd->heredoc = 1;
		else
			cmd->heredoc = 0;
	}
	else
	{
		free(cmd->output_file);
		cmd->output_file = ft_strdup(value);
		if (type == REDIR_APPEND)
			cmd->append = 1;
		else
			cmd->append = 0;
	}
}

void	expand_cmd_redirs(t_cmd *cmd, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redir_types[i] != HERE_DOC)
		{
			expanded = expand_word(cmd->redir_files[i], shell);
			if (expanded)
			{
				free(cmd->redir_files[i]);
				cmd->redir_files[i] = expanded;
			}
		}
		i++;
	}
}
