/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:35:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/04 15:59:43 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_strlen_sep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_count_word(char const *s, char c)
{
	int	count;
	int	in;

	count = 0;
	in = 0;
	if (!*s)
		return (0);
	if (*s != c)
		count++;
	while (*s && *s != c)
		++s;
	if (*s == c)
		++s;
	if (*s)
		++count;
	return (count);
}

static size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(src);
	if (dstsize <= 0)
		return (i);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}

static int	ft_len(int *i, char *s, char c)
{
	int	len;

	if (!(*i))
		len = ft_strlen_sep(s, c);
	else
		len = ft_strlen(s);
	return (len);
}

char	**ft_split_env(char *s, char c)
{
	int		count_word;
	char	**tab;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	count_word = ft_count_word(s, c);
	tab = (char **)ft_malloc(sizeof(char *) * (count_word + 1), 0x1);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < count_word && *s)
	{
		if (*s == c && *s)
			s++;
		len = ft_len(&i, s, c);
		tab[i] = (char *)ft_malloc(sizeof(char) * (len + 1), 0x1);
		if (!tab[i])
			return (NULL);
		ft_strlcpy(tab[i++], s, len + 1);
		s += len;
	}
	tab[count_word] = 0;
	return (tab);
}
