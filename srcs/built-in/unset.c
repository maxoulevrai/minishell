/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:51:22 by root              #+#    #+#             */
/*   Updated: 2026/03/06 16:51:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/bultins.h"

static void	remove_env_node(t_env **envp, t_env *prev, t_env *curr)
{
	if (prev)
		prev->next = curr->next;
	else
		*envp = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

static int	unset_one(t_env **envp, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *envp;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			remove_env_node(envp, prev, curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (0);
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			ft_fprintf(STDERR_FILENO,
				"unset: `%s': not a valid identifier\n", cmd->args[i]);
			ret = 1;
		}
		else
			unset_one(shell->envp, cmd->args[i]);
		i++;
	}
	return (ret);
}
