/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:29:23 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/16 15:11:27 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*single_str(char *input, int *i)
{
	char	*res;
	int		start;

	start = *i;
	while (input[*i] == '$')
		(*i)++;
	while (is_var_char(input[*i]))
		(*i)++;
	res = ft_substr(input, start, *i - start);
	return (res);
}

char	**get_strings(char *input)
{
	char	**result;
	int		i;
	int		start;
	int		count;

	i = 0;
	start = 0;
	count = 0;
	result = ft_malloc(sizeof(char *) * (ft_strlen(input) + 1), 1);
	while (input[i])
	{
		if (input[i] == '$')
			result[count++] = single_str(input, &i);
		else
		{
			start = i;
			while (input[i] && input[i] != '$')
				i++;
			result[count++] = ft_substr(input, start, i - start);
		}
	}
	result[count] = NULL;
	return (result);
}

void	expand_val(t_mini *cmd, char *s, char **tmp1, int flag)
{
	int	a;

	a = 0;
	while (s[a] == '$')
		(a)++;
	if (ft_strlen(s) == a)
		*tmp1 = s;
	else if (s[a] == '?')
	{
		*tmp1 = ft_itoa(cmd->status);
		if (s[a + 1])
			*tmp1 = ft_strjoin(*tmp1, ft_substr(s, a + 1, ft_strlen(s)));
	}
	else
	{
		*tmp1 = get_env_value(cmd->env, ft_substr(s, a, ft_strlen(s)));
		if (flag == 0)
			set_qoats_fl(*tmp1);
	}
}

void	handle_valid_var(char **res, char *input, t_mini *cmd)
{
	char	*val;
	char	*tmp1;
	t_quote	quote;
	int		f;
	char	**s;

	f = 0;
	val = NULL;
	quote.single = 0;
	quote.doubl = 0;
	s = get_strings(input);
	while (s[f])
	{
		check_quotes(&quote, s[f]);
		if (should_expand(s[f]) && !quote.single)
			expand_val(cmd, s[f], &tmp1, 0);
		else
			tmp1 = s[f];
		val = ft_strjoin(val, tmp1);
		f++;
	}
	*res = ft_strjoin(*res, val);
}

void	get_env(char **res, char *input, int *i, t_mini *cmd)
{
	while (input[*i] == '$')
		(*i)++;
	handle_valid_var(res, input, cmd);
}
