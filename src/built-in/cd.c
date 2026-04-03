/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:09:54 by root              #+#    #+#             */
/*   Updated: 2026/04/03 15:49:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// commande cd
// prototype: cd [path]
// sans argument -> va dans HOME
// avec argument -> va dans le path donné

char	*get_env(t_env **envp, char *key);

static void	update_pwd(t_env *envp, char *key, char *dir_path)
{
	t_env	*tmp;
	tmp = envp;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = dir_path;
	}
	else
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return ;
		tmp->key = ft_strdup(key);
		tmp->value = dir_path;
		ft_envadd_back(&envp, tmp);
	}
}

int	update_pwd_vars(t_env *envp, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		free(old_pwd);
		return (1);
	}
	update_pwd(envp, "OLDPWD", old_pwd);
	update_pwd(envp, "PWD", new_pwd);
	return (0);
}

static char	*get_cd_path(t_env *envp, char **cmd_tabl)
{
	char	*oldpwd;
	char	*home;

	if (!cmd_tabl[1])
	{
		home = get_env(&envp, "HOME");
		if (!home)
			return (ft_fprintf(STDERR_FILENO,
					"minishell: cd: HOME not set\n"), NULL);
		return (home);
	}
	else if (ft_strcmp(cmd_tabl[1], "-") == 0)
	{
		oldpwd = get_env(&envp, "OLDPWD");
		if (!oldpwd)
			return (ft_fprintf(STDERR_FILENO,
					"minishell: cd: OLDPWD not set\n"), NULL);
		return (oldpwd);
	}
	else if (cmd_tabl[2])
		return (ft_fprintf(STDERR_FILENO,
				"minishell: cd: too many arguments\n"), NULL);
	else
		return (cmd_tabl[1]);
}

int	ft_cd(t_env *envp, char **cmd_tabl)
{
	char	*path;
	char	*old_pwd;

	path = get_cd_path(envp, cmd_tabl);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_fprintf(STDERR_FILENO, "minishell: pwd: %s\n",
				strerror(errno)), 1);
	if (chdir(path) == -1)
	{
		free(old_pwd);
		return (ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n",
				path, strerror(errno)), 1);
	}
	if (update_pwd_vars(envp, old_pwd) == 1)
		return (1);
	return (0);
}
