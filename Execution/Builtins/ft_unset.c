/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:23:35 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/12 15:25:46 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_unset_target(char *key, char *input_key)
{
	return (!ft_strncmp(key, input_key, ft_strlen(input_key))
		&& ft_strncmp(input_key, "_", 2));
}

void	remove_first_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
}

void	remove_matching_env(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (*env && is_unset_target(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_env **env, char **input)
{
	int	i;

	if (!env || !(*env))
		return (0);
	i = 0;
	while (input && input[i])
	{
		if (*env && is_unset_target((*env)->key, input[i]))
			remove_first_env(env);
		else
			remove_matching_env(env, input[i]);
		++i;
	}
	return (0);
}
