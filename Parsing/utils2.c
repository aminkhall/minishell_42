/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:04:11 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 18:00:25 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_nb(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = len_nb(nb);
	str = (char *)ft_malloc((len + 1), 1);
	if (!str)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	str [len] = '\0';
	while (nb)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}

int	is_delimiter(char *line, char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

char	*ft_itoa_base(void *ptr)
{
	unsigned long	addr;
	char			*base;
	char			buffer[2 + sizeof(unsigned long) * 2 + 1];
	int				i;

	addr = (unsigned long)ptr;
	base = "0123456789abcdef";
	i = sizeof(buffer) - 1;
	buffer[i--] = '\0';
	if (addr == 0)
		buffer[i--] = '0';
	else
	{
		while (addr > 0)
		{
			buffer[i--] = base[addr % 16];
			addr /= 16;
		}
	}
	buffer[i--] = 'x';
	buffer[i] = '0';
	return (ft_strdup(&buffer[i]));
}

void	set_back_qoats(char *result)
{
	int	x;

	x = 0;
	if (!result)
		return ;
	while (result[x])
	{
		if (result[x] == -12)
			result[x] = '\'';
		else if (result[x] == -11)
			result[x] = '"';
		x++;
	}
}
