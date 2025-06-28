/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:14:24 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 14:57:08 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

int	is_operator2(char c)
{
	return (c == '|' || c == '<' || c == '&' || c == ';');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	d_operator(char c, char next)
{
	return ((c == '>' && next == '<')
		|| (c == '<' && next == '>')
		|| (c == '>' && next == '>')
		|| (c == '<' && next == '<')
	);
}
