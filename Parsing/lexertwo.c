/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexertwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:25:20 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/09 16:10:02 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_spaces(char **input)
{
	while (**input && is_space(**input))
		(*input)++;
}

int	is_operator5(char c)
{
	return (c == '&' || c == ';');
}

int	n_isoperator(char *input)
{
	skip_spaces(&input);
	return (*input == '\0' || is_operator5(*input));
}

int	handle_op(char *op, char **input)
{
	if ((*op == '>' && **input == '|') || (*op == '<' && **input == '>')
		|| (*op == '>' && **input == '<'))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	if ((*op == '|' && **input == '|') || (*op == '<' && **input == '|'))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	if (n_isoperator(*input))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	if ((ft_strcmp(op, ">>") == 0 && is_operator(**input)) || (ft_strcmp(op,
				">") == 0 && is_operator(**input)) || (ft_strcmp(op, "<") == 0
			&& is_operator(**input)) || (ft_strcmp(op, "<<") == 0
			&& is_operator(**input)))
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	return (1);
}

int	handle_pipe(char *input)
{
	while (*input && is_space(*input))
		input++;
	if (*input == '|')
	{
		ft_putstr(2, "syntax error\n", 0);
		return (0);
	}
	return (1);
}
