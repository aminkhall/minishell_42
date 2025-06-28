/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:20:47 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 16:29:30 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_operator(char **current, t_val *tkn)
{
	if (d_operator(**current, *(*current + 1)))
		double_operator(current, tkn);
	else
		single_operator(current, tkn);
}

void	process_token(char **current, t_val *tkn, t_mini *cmd)
{
	int	current_index;

	current_index = 0;
	if (is_space(**current))
	{
		(*current)++;
		return ;
	}
	if (is_operator(**current))
	{
		handle_operator(current, tkn);
		if (*(tkn->count) == 0)
			return ;
		tkn->expect_cmd = 1;
		return ;
	}
	if (!(*tkn->count == 0))
	{
		current_index = *tkn->count - 1;
		(*tkn->tokens)[current_index].ambiguous = 0;
	}
	collect_argument(current, tkn, cmd);
}

void	tokens_init(t_val *tkn, t_token *tokens, int *count)
{
	tkn->count = count;
	tkn->expect_cmd = 1;
	tkn->expect_file = 0;
	tkn->to_export = 0;
	tokens->expand = 1;
	tokens->quoted = 0;
	tokens->ambiguous = 0;
	tokens->empty_ex = 0;
	tokens->expanded = 0;
}

t_token	*tokenize(char *input, int *t_count, t_mini *cmd)
{
	t_token	*tokens;
	char	*current;
	int		count;
	t_val	tkn;

	count = 0;
	tokens = NULL;
	tokens = ft_malloc(sizeof(t_token) * (ft_strlen(input) + 2), 0x1);
	if (!tokens)
		return (NULL);
	tkn.tokens = &tokens;
	current = input;
	tokens_init(&tkn, tokens, &count);
	while (*current != '\0')
		process_token(&current, &tkn, cmd);
	if (*(tkn.count) == 0)
		return (NULL);
	if (count != 0)
		tokens = add_token(tokens, &count, T_END, "");
	*t_count = count;
	return (tokens);
}
