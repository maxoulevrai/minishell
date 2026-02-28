/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:46:39 by maleca            #+#    #+#             */
/*   Updated: 2026/02/28 17:48:55 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// copie la ce qui se trouve avant le '=' 
// dans la variable d'environnement (aka the key)

char	*get_env_key(char *env_line) 
{
	int	i;

	i = 0;
	while (env_line[i] != '=' && env_line[i])
		i++;
	if (env_line[i] == 0)
		return (NULL);
	return (ft_strndup(env_line, i));
}

// copie la ce qui se trouve apres le '=' 
// dans la variable d'environnement (aka the value)

char	*get_env_value(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i] != '=' && env_line[i])
		i++;
	if (env_line[i] == 0)
		return (NULL);
	return (ft_strdup(&env_line[i + 1]));
}

// init de la nouvelle node (duuh)

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

t_env	*env_cpy(char **envp)
{
	t_env	*head;
	t_env	*new;
	size_t	i;

	if (!envp)
			return (NULL); // sortie propre a gerer
	i = 0;
	head = NULL;
	while (envp[i])
	{
		new = init_env_node(envp[i]);
		if (!new)
			return (NULL); // sortie propre a gerer
		ft_envadd_back(&head, new);
		i++;
	}
	return (head);
}

int main(int ac, char **av, char **envp)
{
	t_env *envpp;
	t_env	*tmp;
	// int		i = 0;

	(void)ac;
	(void)av;
	envpp = env_cpy(envp);
	tmp = envpp;
	while (tmp != NULL)
	{
		ft_printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
	// ft_printf("LEVRAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
	// while (envp[i])
	// {
	// 	ft_printf("%s\n", envp[i]);
	// 	i++;
	// }

	return (0);
}
