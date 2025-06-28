/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:29:40 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/16 15:07:40 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**handle_quoted(char *s, int quoted)
{
	char	**split;
	int		i[2];
	char	**split2;

	if (quoted)
		split = quote_case(s);
	else
		split = ft_split(s, ' ');
	if (is_space(s[0]) || is_space(ft_strlen(s) - 1))
	{
		split2 = (char **)ft_malloc(sizeof(char *) * (count(split) + 3), 1);
		if (is_space(s[0]))
			split2[0] = ft_strdup("");
		i[0] = 1;
		i[1] = 0;
		while (split[i[1]])
			split2[i[0]++] = split[i[1]++];
		if (is_space(s[ft_strlen(s) - 1]))
		{
			split2[i[0]] = " ";
			i[0]++;
		}
		return (split2[i[0]] = NULL, split2);
	}
	return (split);
}

int	fill_key(char **res, char **p1, int *i, int *j)
{
	int	flag;

	flag = 0;
	if ((ft_strlen(p1[*j]) == 0) && *j == 0)
		(*j)++;
	if ((p1[*j] && ft_strlen(p1[*j]) != 0) && p1[*j][0] == ' ')
	{
		flag = 1;
		return (1);
	}
	res[(*i)++] = p1[(*j)++];
	return (0);
}

char	**join_split_parts(char **p1, int first_quot, int second_quot, char *s)
{
	int		i[3];
	char	**res;
	char	**p2;

	(1) && (i[0] = 0, i[1] = 0, i[2] = 0);
	p2 = handle_quoted(s, second_quot && !first_quot);
	res = (char **)ft_malloc(sizeof(char *) * (count(p1) + count(p2) + 1), 0x1);
	while (i[0] < count(p1) - 1)
	{
		if (fill_key(res, p1, &i[0], &i[2]) == 1)
		{
			i[1] = 1;
			break ;
		}
	}
	res[i[0]++] = ft_strjoin3(p1[count(p1) - 1], "=", p2[0], i[1]);
	i[2] = 1;
	while (i[2] < count(p2))
	{
		if ((i[2] == (count(p2) - 1) && p2[i[2]][0] == ' '))
			break ;
		res[i[0]++] = ft_strdup(p2[i[2]++]);
	}
	return (res[i[0]] = NULL, res);
}

char	**split_rs(char *result)
{
	char	*eq;
	char	*f;
	char	*s;
	int		first_second[2];
	char	**p1;

	eq = ft_strchr(result, '=');
	if (!eq || eq == result)
	{
		if ((result[0] == '"' && result[ft_strlen(result) - 1] == '"')
			|| (result[0] == '\'' && result[ft_strlen(result) - 1] == '\''))
			return (quote_case(result));
		return (ft_split(result, ' '));
	}
	f = ft_substr(result, 0, eq - result);
	s = ft_strdup(eq + 1);
	first_second[0] = ((f[0] == '"' && f[ft_strlen(f) - 1] == '"')
			|| (f[0] == '\'' && f[ft_strlen(f) - 1] == '\''));
	first_second[1] = ((s[0] == '"' && s[ft_strlen(s) - 1] == '"')
			|| (s[0] == '\'' && s[ft_strlen(s) - 1] == '\''));
	p1 = handle_quoted(f, first_second[0]);
	return (join_split_parts(p1, first_second[0], first_second[1], s));
}
