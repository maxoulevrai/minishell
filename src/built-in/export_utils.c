/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:11:09 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:11:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	appen_export_var(t_env **envp, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(key);
		free(value);
		return (1);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	ft_envadd_back(envp, new);
	return (0);
}

int	add_var_to_env(t_env **envp, char *key, char *value)
{
	t_env	*tmp;

	if (!key)
		return (1);
	tmp = *envp;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp && value)
	{
		free(tmp->value);
		tmp->value = value;
		free(key);
	}
	else if (!tmp)
		return (appen_export_var(envp, key, value));
	else
		free(key);
	return (0);
}

// int		add_export_to_env(t_env **envp, char *key, char *value)
// {
// 	t_env	*tmp;
// 	t_env	*new;
// 	char	*new_value;

// 	tmp = *envp;
// 	while (tmp && ft_strcmp(tmp->key, key) != 0)
// 		tmp = tmp->next;
// 	if (tmp && value)
// 		return (new_value = ft_strdup(value),
// 			new_value && (free(tmp->value), tmp->value = new_value),0);
// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->key = ft_strdup(key);
// 	if (value)
// 		new->value = ft_strdup(value);
// 	if (!new->key)
// 		return (free(new->key), free(new->value), free(new));
// 	new->next = NULL;
// 	ft_envadd_back(envp, new);
// }

void	set_env_var(t_env **envp, char *arg)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!ft_strchr(arg, '='))
		key = ft_strdup(arg);
	else
	{
		key = get_env_key(arg);
		value = get_env_value(arg);
	}
	if (!key)
		return ;
	add_var_to_env(envp, key, value);
}
