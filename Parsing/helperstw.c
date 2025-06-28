/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperstw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:15:41 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/16 15:10:53 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3, int flag)
{
	char	*tmp;
	char	*res;

	if (flag == 1)
		res = ft_strjoin("=", s3);
	else
	{
		tmp = ft_strjoin(s1, s2);
		res = ft_strjoin(tmp, s3);
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	str = (char *)ft_malloc((ft_strlen(s1) + ft_strlen(s2)) + 1, 0x1);
	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	return (str);
}

char	**quote_case(char *result)
{
	char	**arr;

	arr = (char **)ft_malloc(sizeof(char *) * 2, 0x1);
	arr[0] = result;
	arr[1] = NULL;
	return (arr);
}

int	count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
