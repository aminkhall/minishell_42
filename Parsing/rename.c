/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:50:56 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 17:15:30 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;
	size_t	len_s;

	if (!s || len < 0)
		return (NULL);
	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	s2 = (char *)ft_malloc(len + 1, 0x1);
	if (!s2)
		return (NULL);
	while (i < len)
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}

void	set_qoats_fl(char *result)
{
	int	x;

	x = 0;
	if (!result)
		return ;
	while (result[x])
	{
		if (result[x] == '\'' || result[x] == '"')
		{
			if (result[x] == '\'')
				result[x] = -12;
			else
				result[x] = -11;
		}
		x++;
	}
}

char	*ft_remove_qoats(char *s)
{
	int		i;
	char	quote;
	char	*result;

	if (!s)
		return (NULL);
	i = 0;
	quote = 0;
	result = ft_malloc(ft_strlen(s) + 1, 0x1);
	if (!result)
		return (NULL);
	remove_qu(s, result);
	if (quote)
		return (ft_strdup(s));
	return (result);
}

void	double_operator(char **current, t_val *tkn)
{
	char	*op;

	op = ft_strndup(*current, 2);
	*current += 2;
	tkn->expect_file = 1;
	*(tkn->tokens) = add_token(*(tkn->tokens), tkn->count, T_OP, op);
}

void	single_operator(char **current, t_val *tkn)
{
	char	*op;

	op = ft_strndup(*current, 1);
	if (**current == '|')
	{
		tkn->expect_file = 0;
		(*tkn->tokens)->ambiguous = 0;
	}
	else
	{
		tkn->expect_file = 1;
		tkn->expect_cmd = 0;
	}
	(*current)++;
	*(tkn->tokens) = add_token(*(tkn->tokens), tkn->count, T_OP, op);
}
