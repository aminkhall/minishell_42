/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:20 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/16 14:18:39 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '-' || code[i] == '+')
		++i;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
			return (1);
		++i;
	}
	return (0);
}

int	arg_count(char **input)
{
	int	count;

	count = 0;
	while (input[count])
	{
		++count;
	}
	return (count);
}

void	ft_error(int flag)
{
	if (flag == 1)
	{
		ft_malloc(0, 0);
		printf("exit\n");
	}
	return ;
}

void	ft_exit(char **code, int *status)
{
	int	num;

	if (!code || !*code)
		(ft_error(1), exit(0));
	if (is_numeric(*code))
	{
		ft_error(1);
		perror("numeric argument required");
		exit(2);
	}
	else if (arg_count(code) != 1)
	{
		printf("exit\n");
		perror("too many arguments");
		*status = 1;
		return ;
	}
	else if (!ft_strncmp(*code, "-9223372036854775808", 21))
		(ft_error(1), exit(0));
	num = ft_atoi(*code);
	ft_error(1);
	exit(num);
}
