/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:31:29 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/01 19:13:12 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew(char *key, char *value, char *all)
{
	t_env	*new_node;

	new_node = ft_malloc(sizeof(t_env), 0x1);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->all = ft_strdup(all);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = (*lst);
	while ((tmp)->next)
		(tmp) = (tmp)->next;
	(tmp)->next = new;
}

char	**env_notfound(void)
{
	char	**env;
	char	*tmp_pwd;
	char	*curr_pwd;
	char	*str;
	char	*path;

	tmp_pwd = getcwd(NULL, 0);
	curr_pwd = ft_strdup(tmp_pwd);
	free(tmp_pwd);
	curr_pwd = ft_join("PWD=", curr_pwd);
	str = ft_join("OLDPWD ", curr_pwd);
	str = ft_join(str, " SHLVL=1");
	path = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:"
			"/usr/sbin:/usr/bin:/sbin:/bin ");
	str = ft_join(path, str);
	env = ft_split(str, ' ');
	return (env);
}

t_env	*creat_lst(char **env)
{
	int		i;
	char	**tmp;
	t_env	*lst;
	t_env	*tmp_lst;

	if (!env || !(*env))
		env = env_notfound();
	i = 0;
	lst = NULL;
	tmp_lst = lst;
	while (env && env[i])
	{
		tmp = ft_split_env(env[i], '=');
		if (!tmp || !*tmp)
			break ;
		tmp_lst = ft_lstnew(tmp[0], tmp[1], env[i]);
		ft_lstadd_back(&lst, tmp_lst);
		++i;
	}
	return (lst);
}

t_env	*creat_copy(t_env **env)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*copy;

	copy = NULL;
	tmp = (*env);
	while (tmp)
	{
		new = ft_lstnew(tmp->key, tmp->value, tmp->all);
		if (!new)
			return (NULL);
		ft_lstadd_back(&copy, new);
		tmp = tmp->next;
	}
	return (copy);
}
