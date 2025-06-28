/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:33:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/05/31 15:35:30 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd_entry(t_env *tmp, char *path, int *flag)
{
	char	*pwd;
	char	*tmp_pwd;
	char	*str;
	char	*tmp_str;

	tmp_pwd = getcwd(NULL, 0);
	if (!tmp_pwd)
	{
		str = ft_join(tmp->value, "/");
		pwd = ft_join(str, path);
		*flag = 1;
	}
	else
	{
		pwd = ft_strdup(tmp_pwd);
		free(tmp_pwd);
	}
	tmp->value = ft_strdup(pwd);
	tmp_str = ft_join(tmp->key, "=");
	tmp->all = ft_join(tmp_str, pwd);
}

void	update_oldpwd_entry(t_env *tmp, char *tmp_oldpwd)
{
	char	*old_pwd;

	old_pwd = ft_strdup(tmp_oldpwd);
	tmp->value = ft_strdup(old_pwd);
	tmp->all = ft_join(tmp->key, "=");
	tmp->all = ft_join(tmp->all, old_pwd);
}

void	add_missing_pwd(t_env **env, char *tmp_oldpwd,
		char *path, int *flag)
{
	char	*tmp_pwd;
	char	*pwd;
	char	*s;
	char	*tmp;
	t_env	*new;

	tmp_pwd = getcwd(NULL, 0);
	if (!tmp_pwd)
	{
		tmp_pwd = ft_join(tmp_oldpwd, "/");
		pwd = ft_join(tmp_pwd, path);
		*flag = 1;
	}
	else
	{
		pwd = ft_strdup(tmp_pwd);
		free(tmp_pwd);
	}
	tmp = ft_join("PWD", "=");
	s = ft_join(tmp, pwd);
	new = ft_lstnew("PWD", pwd, s);
	ft_lstadd_back(env, new);
}

void	add_missing_oldpwd(t_env **env, char *tmp_oldpwd)
{
	char	*old_pwd;
	char	*s;
	char	*tmp;
	t_env	*new;

	old_pwd = ft_strdup(tmp_oldpwd);
	tmp = ft_join("OLDPWD", "=");
	s = ft_join(tmp, old_pwd);
	new = ft_lstnew("OLDPWD", old_pwd, s);
	ft_lstadd_back(env, new);
}
