/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:22:47 by root              #+#    #+#             */
/*   Updated: 2026/03/23 15:05:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static char	*dup_env_entry(t_env *node)
{
	char	*tmp;
	char	*entry;

	if (!node->value)
		return (ft_strdup(node->key));
	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, node->value);
	free(tmp);
	return (entry);
}

char	**convert_env_to_tab(t_env *envp)
{
	char	**env_tab;
	t_env	*tmp;
	int		len;
	int		i;

	len = 0;
	tmp = envp;
	while (tmp && ++len)
		tmp = tmp->next;
	env_tab = malloc(sizeof(char *) * (len + 1));
	if (!env_tab)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		env_tab[i] = dup_env_entry(tmp);
		if (!env_tab[i])
			return (free_dtab(env_tab), NULL);
		tmp = tmp->next;
		i++;
	}
	return (env_tab[i] = NULL, env_tab);
}

static void	sort_n_print_env(char **env_tab)
{
	int		size;
	int		i;
	int		j;

	size = 0;
	while (env_tab[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env_tab[j], env_tab[j + 1]) > 0)
				ft_dtab_swap(&env_tab[j], &env_tab[j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (env_tab[i])
		ft_fprintf(STDOUT_FILENO, "%s\n", env_tab[i++]);
}

static void	set_env_var(t_env **envp, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;
	char	*new_value;

	tmp = *envp;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp)
		return (new_value = ft_strdup(value),
			new_value && (free(tmp->value), tmp->value = new_value), (void)0);
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
		return (free(new->key), free(new->value), free(new));
	new->next = NULL;
	ft_envadd_back(envp, new);
}

int	ft_export(t_env *envp, char **args)
{
	char	**env_tab;
	char	*key;
	char	*value;

	if (!args[1])
	{
		env_tab = convert_env_to_tab(envp);
		if (!env_tab)
			return (1);
		sort_n_print_env(env_tab);
		free_dtab(env_tab);
		return (0);
	}
	if (!ft_strchr(args[1], '='))
		return (ft_fprintf(STDERR_FILENO,
				"6ft shell: export: `%s': not a valid identifier\n",
				args[1]), 1);
	key = get_env_key(args[1]);
	value = get_env_value(args[1]);
	if (!key || !value)
		return (free(key), free(value), 1);
	set_env_var(&envp, key, value);
	free(key);
	free(value);
	return (0);
}
