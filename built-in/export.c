/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:22:47 by root              #+#    #+#             */
/*   Updated: 2026/03/07 19:29:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bultins.h"

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
			env_tab[i] = ft_strjoin(tmp_str, tmp->value);
			free(tmp_str);
		}
		else
			env_tab[i] = ft_strdup(tmp->key);
		if (!env_tab[i])
			return (NULL);
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
	char	*tmp;

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

	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	ft_envadd_back(envp, new);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	char	**env_tab;
	char	*key;
	char	*value;
	int		i;

	if (!cmd->args[1])
	{
		env_tab = convert_env_to_tab(shell->envp);
		if (!env_tab)
			return (1);
		sort_n_print_env(env_tab);
		i = 0;
		while (env_tab[i])
			free(env_tab[i++]);
		return (free(env_tab), 0);
	}
	if (!ft_strchr(cmd->args[1], '='))
	{
		ft_fprintf(STDERR_FILENO,
			"export: `%s': not a valid identifier\n", cmd->args[1]);
		return (1);
	}
	key = get_env_key(cmd->args[1]);
	value = get_env_value(cmd->args[1]);
	set_env_var(shell->envp, key, value);
	return (0);
}
