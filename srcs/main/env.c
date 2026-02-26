/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:46:39 by maleca            #+#    #+#             */
/*   Updated: 2026/02/26 16:22:36 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*get_env_key(char *env_line)
{
	char *env_key;
	int	i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	return (ft_strndup(env_line, i));
}

char	*get_env_value(char *env_line)
{
	char *env_value;
	int	i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	return (ft_strdup(&env_line[i]))
}

t_env	*init_env_node(char	*env_line, size_t idx)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_env_key;
	node->value = get_env_value;
	node->id = idx;
	node->next = NULL;
	return (node);
}

t_env	*env_cpy(t_list **lst, char	**envp)
{
	t_list	*first;
	t_list	*new;
	size_t	i;

	i = 0;
	first = NULL;
	while (envp[i])
	{
		new = init_env_node(envp[i], i);
		if (!new)
		{
			while (first)
			{
				new = first->next;
				free(first);
				first = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
