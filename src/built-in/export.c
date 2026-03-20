/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:22:47 by root              #+#    #+#             */
/*   Updated: 2026/03/20 04:27:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	env_list_size(t_env *envp)
{
	int	count;

	count = 0;
	while (envp)
	{
		count++;
		envp = envp->next;
	}
	return (count);
}

char	**convert_env_to_tab(t_env *envp)
{
	char	**env_tab;
	t_env	*tmp;
	char	*tmp_str;
	int		i;

	env_tab = malloc(sizeof(char *) * (env_list_size(envp) + 1));
	if (!env_tab)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp_str = ft_strjoin(tmp->key, "=");
			if (!tmp_str)
				return (free_dtab(env_tab), NULL);
			env_tab[i] = ft_strjoin(tmp_str, tmp->value);
			free(tmp_str);
		}
		else
			env_tab[i] = ft_strdup(tmp->key);
		if (!env_tab[i])
			return (free_dtab(env_tab), NULL);
		i++;
		tmp = tmp->next;
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
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return ;
			free(tmp->value);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return ;
	}
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
	{
		ft_fprintf(STDERR_FILENO,
			"export: `%s': not a valid identifier\n", args[1]);
		return (1);
	}
	key = get_env_key(args[1]);
	value = get_env_value(args[1]);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	set_env_var(&envp, key, value);
	free(key);
	free(value);
	return (0);
}
