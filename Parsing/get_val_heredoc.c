/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:35:22 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/15 16:57:42 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_char(char c)
{
	return (isalnum(c) || c == '_' || c == '?');
}

void	quotes_case(t_quote *q, char c)
{
	if (c == '\'' && !q->doubl)
		q->single = !q->single;
	else if (c == '"' && !q->single)
		q->doubl = !q->doubl;
}

void	check_quotes(t_quote *quote, char *s)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		quotes_case(quote, s[i]);
		i++;
	}
}

void	handle_valid_var_heredoc(char **res, char *input, t_mini *cmd)
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
		if (should_expand(s[f]))
			expand_val(cmd, s[f], &tmp1, 1);
		else
			tmp1 = s[f];
		val = ft_strjoin(val, tmp1);
		f++;
	}
	*res = ft_strjoin(*res, val);
}

void	get_env_heredoc(char **res, char *input, int *i, t_mini *cmd)
{
	while (input[*i] == '$')
		(*i)++;
	handle_valid_var_heredoc(res, input, cmd);
}
