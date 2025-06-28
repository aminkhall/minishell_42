/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:15 by mkhallou          #+#    #+#             */
/*   Updated: 2025/05/31 15:39:36 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_n(char *av)
{
	int	i;

	if (!av)
		return (1);
	i = 0;
	if (av[i] == '-' && av[i + 1] == 'n')
	{
		++i;
		while (av[i] == 'n')
			++i;
		if (!av[i])
			return (0);
	}
	return (1);
}

int	ft_echo(char **av)
{
	int	n;
	int	flag;

	if (!av)
		ft_putstr(1, "\n", 0);
	n = 1;
	flag = 1;
	while (*av)
	{
		if (flag && !check_n(*av))
			n = 0;
		else
		{
			ft_putstr(1, *av, 0);
			flag = 0;
			if (*(av + 1))
				ft_putstr(1, " ", 0);
		}
		++av;
	}
	if (n)
		ft_putstr(1, "\n", 0);
	return (0);
}
