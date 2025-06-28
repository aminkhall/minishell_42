/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:22 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/01 18:52:13 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_env(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (tmp->next && ft_strncmp(tmp->key, tmp->next->key,
				ft_strlen(tmp->key)) > 0)
		{
			ft_swap(&(tmp->key), &(tmp->next->key));
			ft_swap(&(tmp->value), &(tmp->next->value));
			ft_swap(&tmp->all, &tmp->next->all);
			tmp = (*env);
		}
		else
			tmp = tmp->next;
	}
}

void	print_env(t_env **env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = NULL;
	copy = creat_copy(env);
	swap_env(&copy);
	tmp = copy;
	while (tmp)
	{
		if (tmp->key && ft_strncmp(tmp->key, "_", 2))
		{
			ft_putstr(1, "declare -x ", 0);
			ft_putstr(1, tmp->all, 1);
			ft_putstr(1, "\n", 0);
		}
		tmp = tmp->next;
	}
}

void	exp_case(t_env **env, char *input)
{
	char	**tab;

	if (!input)
		return ;
	tab = ft_split_env(input, '=');
	if (!tab)
		return ;
	if (!ft_strncmp(tab[0], "_", 2))
		return ;
	if (!add_sign(tab[0]))
	{
		tab[0] = ft_strdup(tab[0]);
		add(env, tab, input);
	}
	else if (!check_key(env, tab[0]))
		found_key(env, tab, input);
	else
		key_notfound(env, tab, input);
	return ;
}

int	ft_export(t_env **env, char **input)
{
	int	i;
	int	status;

	status = 0;
	if (input && *input && **input)
	{
		i = 0;
		while (input[i])
		{
			if (!is_valid(input[i]))
				exp_case(env, input[i]);
			else
			{
				perror("minishell: export: not a valid identifier");
				status = 1;
			}
			++i;
		}
	}
	else
		print_env(env);
	return (status);
}
