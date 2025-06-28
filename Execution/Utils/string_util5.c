/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:14:21 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/15 17:04:21 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	if (!str || !(*str))
		return (0);
	len = 0;
	while (str[len])
		++len;
	return (len);
}

int	ft_strncmp(char *s1, char *s2, int size)
{
	if (!s1 || !s2 || size <= 0)
		return (0);
	while (*s1 && (*s1 == *s2) && size)
	{
		++s1;
		++s2;
		--size;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_copy(char *dst, char *src)
{
	if (!src)
		return ;
	while (*src)
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = '\0';
	return ;
}

void	ft_cat(char *dst, char *src)
{
	int	len;

	if (!src)
		return ;
	len = ft_strlen(dst);
	ft_copy(dst + len, src);
	return ;
}

char	*ft_strdup(char *str)
{
	char	*copy;

	if (!str)
		return (NULL);
	copy = ft_malloc(ft_strlen(str) + 1, 0x1);
	if (!copy)
		return (NULL);
	ft_copy(copy, str);
	return (copy);
}
