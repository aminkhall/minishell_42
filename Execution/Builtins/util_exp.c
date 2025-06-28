/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:48:33 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/01 18:49:15 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_sign(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] && input[i] != '=')
	{
		if (input[i] == '+')
		{
			input[i] = '\0';
			return (0);
		}
		++i;
	}
	return (1);
}

int	is_valid(char *input)
{
	if (!input)
		return (1);
	if (*input == '=' || ft_isdigit(*input) || *input == '+')
		return (1);
	while (*input && *input != '=')
	{
		if (!ft_isalpha(*input) && !ft_isdigit(*input)
			&& *input != '_' && *input != '+')
			return (1);
		if (*input == '+' && *(input + 1) != '=')
			return (1);
		++input;
	}
	return (0);
}

int	ft_find(char *str, char c)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == c)
			return (0);
		++str;
	}
	return (1);
}

int	check_key(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (key && !ft_strncmp(tmp->key, key, ft_strlen(key)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
