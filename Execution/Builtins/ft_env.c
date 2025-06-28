/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:29 by mkhallou          #+#    #+#             */
/*   Updated: 2025/05/31 15:40:07 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !(*env))
		return (0);
	tmp = (*env);
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			ft_putstr(1, (tmp)->all, 0);
			ft_putstr(1, "\n", 0);
		}
		(tmp) = (tmp)->next;
	}
	return (0);
}
