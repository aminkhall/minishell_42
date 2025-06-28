/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:51:30 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/12 15:26:03 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	found_key(t_env **env, char **tab, char *input)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tab[0] && !tab[1] && !ft_strncmp(tmp->key, tab[0],
				ft_strlen(tab[0])))
		{
			if (!ft_find(input, '='))
			{
				tmp->value = NULL;
				tmp->all = ft_join(tab[0], "=");
			}
			break ;
		}
		else if (tab[0] && tab[1] && !ft_strncmp(tmp->key, tab[0],
				ft_strlen(tab[0])))
		{
			tmp->value = ft_strdup(tab[1]);
			tmp->all = ft_strdup(input);
			break ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	key_notfound(t_env **env, char **tab, char *input)
{
	t_env	*new;

	new = NULL;
	new = ft_lstnew(tab[0], tab[1], input);
	if (new)
		ft_lstadd_back(env, new);
	return ;
}

int	add_keyfound(t_env *env, char **tab, char *input)
{
	if (tab[0] && !tab[1] && !ft_strncmp(env->key, tab[0], ft_strlen(tab[0])))
	{
		if (!ft_find(input, '='))
			env->all = ft_join(tab[0], "=");
		return (0);
	}
	else if (tab[0] && tab[1] && !ft_strncmp(env->key, tab[0],
			ft_strlen(tab[0])))
	{
		env->value = ft_join(env->value, tab[1]);
		env->all = ft_join(env->key, "=");
		env->all = ft_join(env->all, env->value);
		return (0);
	}
	return (1);
}

void	add(t_env **env, char **tab, char *input)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!add_keyfound(tmp, tab, input))
			return ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		input = ft_join(tab[0], "=");
		input = ft_join(input, tab[1]);
		key_notfound(env, tab, input);
	}
	return ;
}
