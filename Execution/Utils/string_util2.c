/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:36 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/04 15:58:48 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putstr(int fd, char *str, int flag)
{
	int	sign;

	if (!str)
		return ;
	sign = 0;
	while (*str)
	{
		write(fd, &(*str), 1);
		if (!sign && flag && *str == '=')
		{
			write(1, "\"", 1);
			sign = 1;
		}
		++str;
	}
	if (flag && sign && !(*str))
		write(fd, "\"", 1);
	return ;
}

char	*ft_join(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	new_str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0x1);
	if (!new_str)
		return (NULL);
	ft_copy(new_str, s1);
	ft_cat(new_str, s2);
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	if (!s)
		return (NULL);
	tmp = (char *)s;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == (char)c)
			return (tmp + i);
		i++;
	}
	if (tmp[i] == (char)c)
		return (tmp + i);
	return (NULL);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
