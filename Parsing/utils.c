/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:50:49 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 21:21:31 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	create_token(t_type type, char *value, t_token *tokens)
{
	t_token	token;

	token.type = type;
	token.quoted = tokens->quoted;
	token.ambiguous = tokens->ambiguous;
	token.empty_ex = tokens->empty_ex;
	token.expanded = tokens->expanded;
	token.value = ft_strdup(value);
	token.expand = 1;
	return (token);
}

t_token	*add_token(t_token *tokens, int *count, int type, char *value)
{
	int	last_index;

	if (*count != 0)
		last_index = *count - 1;
	else
		last_index = 0;
	tokens[*count] = create_token(type, value, &tokens[last_index]);
	(*count)++;
	return (tokens);
}
