/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:20:12 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/09 16:10:22 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	val_quote(char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (*input == '"' && !s_quote)
			d_quote = !d_quote;
		input++;
	}
	if (s_quote || d_quote)
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	return (1);
}

int	in_quotes(char c, int *s_quote, int *d_quote)
{
	if (c == '\'' && !(*d_quote))
		*s_quote = !(*s_quote);
	else if (c == '"' && !(*s_quote))
		*d_quote = !(*d_quote);
	return (1);
}

int	fill_operator(char *input, char *op, char **op_start)
{
	int	i;

	op[0] = *input;
	op[1] = '\0';
	*op_start = input;
	if (((*input == '>' || *input == '<') && *(input + 1) == *input)
		|| (*input == '|' && (*(input + 1) == '<' || *(input + 1) == '>')))
	{
		op[1] = *(input + 1);
		op[2] = '\0';
	}
	i = 0;
	if (input[i] == '|' && input[i + 1] == '<' && is_operator(input[i + 3]))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	else
		return (1);
}

int	operator(char *op, char **input)
{
	char	*after_op;

	(*input)++;
	if (op[1] != '\0')
		(*input)++;
	after_op = *input;
	skip_spaces(input);
	if (op[0] == '|' && after_op == *input && (**input == '>'))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	if (!handle_op(op, input))
		return (0);
	return (1);
}

int	validate_operators(char *input)
{
	char	op[3];
	char	*op_start;
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	if (!handle_pipe(input) || !val_quote(input))
		return (0);
	while (*input)
	{
		if (!in_quotes(*input, &s_quote, &d_quote) && (s_quote || d_quote))
			;
		if (!s_quote && !d_quote && is_operator(*input))
		{
			if (!fill_operator(input, op, &op_start))
				return (0);
			if (!operator(op, &input))
				return (0);
			continue ;
		}
		input++;
	}
	return (1);
}
