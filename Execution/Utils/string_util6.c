/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:10:06 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/11 16:54:42 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	cp;

	cp = 0;
	while (lst)
	{
		cp++;
		lst = lst->next;
	}
	return (cp);
}

int	check_path(char **tab)
{
	int	i;

	if (!tab || !(*tab))
		return (0);
	i = 0;
	while (tab && tab[i])
	{
		if (tab[i] && !ft_strncmp(tab[i], "PATH", 5))
			return (1);
		++i;
	}
	return (0);
}

void	add_path(char **tab, int *i)
{
	if (!tab || !(*tab))
		return ;
	if (!check_path(tab))
	{
		tab[*i] = ft_strdup("PATH=\"/usr/local/sbin:"
				"/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\"");
		++(*i);
	}
	tab[*i] = 0;
	return ;
}

char	**arr_env(t_env *env)
{
	int		count;
	char	**tab;
	t_env	*tmp;
	int		i;

	if (!env)
		return (NULL);
	count = ft_lstsize(env);
	tab = ft_malloc(sizeof(char *) * (count + 2), 1);
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (i < count && tmp)
	{
		if (tmp->key && tmp->value)
		{
			tab[i] = ft_strdup(tmp->all);
			++i;
		}
		tmp = tmp->next;
	}
	tab[i] = 0;
	add_path(tab, &i);
	return (tab);
}
