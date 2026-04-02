/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:45:40 by root              #+#    #+#             */
/*   Updated: 2026/03/31 21:15:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = next;
	}
}

t_env	*init_env_node(char	*env_line)
{
	t_env	*node;

	if (!env_line)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_env_key(env_line);
	node->value = get_env_value(env_line);
	if (!node->key)
	{
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

// ajout de la bouvelle node a la fin de la liste chainée 

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head && !new)
		return ;
	if (!*head)
	{
		(*head) = new;
		return ;
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// fonction pour copier l'env dans son ensemble et le convert
// en liste chainee (modification dynamique de l'env beaucoup plus simple
// pour des fonction comme export ou unset cf builtins)

t_env	*env_dup(char **envp)
{
	t_env	*head;
	t_env	*new;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	head = NULL;
	while (envp[i])
	{
		new = init_env_node(envp[i]);
		if (!new)
		{
			free_env_list(head);
			return (NULL);
		}
		ft_envadd_back(&head, new);
		i++;
	}
	return (head);
}
