/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:07 by mkhallou          #+#    #+#             */
/*   Updated: 2025/05/31 15:33:19 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(t_env **env, char *value)
{
	t_env	*tmp;
	char	*pwd;

	pwd = NULL;
	tmp = (*env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, value, ft_strlen(value)))
		{
			pwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (pwd);
}

static int	handle_successful_cd(t_env **env, t_env *tmp,
		char *path, char *tmp_oldpwd)
{
	int	flags[3];

	(1) && (flags[0] = 0, flags[1] = 0, flags[2] = 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 4))
		{
			update_pwd_entry(tmp, path, &flags[2]);
			flags[0] = 1;
		}
		else if (!ft_strncmp(tmp->key, "OLDPWD", 7))
		{
			update_oldpwd_entry(tmp, tmp_oldpwd);
			flags[1] = 1;
		}
		tmp = tmp->next;
	}
	if (!flags[0])
		add_missing_pwd(env, tmp_oldpwd, path, &flags[2]);
	if (!flags[1])
		add_missing_oldpwd(env, tmp_oldpwd);
	if (flags[2])
		printf("cd: error retrieving current directory: getcwd:"
			"cannot access parent directories: No such file or directory\n");
	return (0);
}

char	*ft_getcwd(t_env **env, char *pwd)
{
	char	*tmp_oldpwd;
	char	*old_pwd;

	tmp_oldpwd = getcwd(NULL, 0);
	old_pwd = ft_strdup(tmp_oldpwd);
	free(tmp_oldpwd);
	if (!old_pwd)
		old_pwd = get_value(env, "PWD");
	if (!old_pwd)
		old_pwd = ft_strdup(pwd);
	return (old_pwd);
}

int	ft_cd(t_env **env, char **path, char *pwd)
{
	t_env	*tmp;
	char	*old_pwd;

	if (!env || !(*env))
		return (1);
	if (*path && *((path + 1)))
	{
		perror("too many arguments");
		return (1);
	}
	if (*path && !(**path))
		return (0);
	if (!(*path))
		(*path) = get_value(env, "HOME");
	old_pwd = ft_getcwd(env, pwd);
	if (!chdir(*path))
	{
		tmp = *env;
		return (handle_successful_cd(env, tmp, *path, old_pwd));
	}
	else
		return (perror(*path), 1);
}
