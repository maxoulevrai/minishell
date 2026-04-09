/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:09:51 by root              #+#    #+#             */
/*   Updated: 2026/04/09 19:09:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static char	*dup_env_entry(t_env *node)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*entry;

	if (!node->value)
		return (ft_strdup(node->key));
	tmp_1 = ft_strjoin(node->key, "=\"");
	if (!tmp_1)
		return (NULL);
	if (node->value)
	{
		tmp_2 = ft_strjoin(tmp_1, node->value);
		if (!tmp_2)
			return (free(tmp_1), NULL);
		free(tmp_1);
		entry = ft_strjoin(tmp_2, "\"");
		if (!entry)
			return (free(tmp_2), NULL);
		free(tmp_2);
	}
	else
		return (tmp_1);
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
		ft_fprintf(STDOUT_FILENO, "export %s\n", env_tab[i++]);
}

int	parse_export(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i])
		return (2);
	return (1);
}

int	ft_export(t_shell *data, char **args)
{
	char	**env_tab;
	int		i;

	if (!args[1])
	{
		env_tab = convert_env_to_tab(data->envp);
		if (!env_tab)
			return (1);
		sort_n_print_env(env_tab);
		free_dtab(env_tab);
		return (0);
	}
	i = 0;
	while (args[++i])
	{
		if (parse_export(args[i]))
			set_env_var(&data->envp, args[i]);
		else
		{
			ft_fprintf(STDERR_FILENO,
				"6ft shell: export: '%s': not a valid identifier\n", args[i]);
			data->last_status = 1;
		}
	}
	return (data->last_status);
}
