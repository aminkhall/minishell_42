/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:51:11 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 21:22:43 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

char	*ft_strndup(char *s1, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_malloc(n + 1, 0x1);
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	full_space(char	*str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) && str[i] != 0)
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_delete	*lstnew(void *str)
{
	t_delete	*lst;

	lst = malloc(sizeof(t_delete));
	if (!lst)
		return (NULL);
	lst->ptr = str;
	lst->next = NULL;
	return (lst);
}
