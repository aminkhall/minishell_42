/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:36:43 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 16:34:33 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_expand_var(char *arg, t_val *tkn)
{
	int	has_equal;
	int	start_d;

	has_equal = ft_strchr(arg, '=') != NULL;
	start_d = arg[0] == '$';
	if (!tkn->expect_file && (!has_equal || (start_d && should_expand(arg))))
		return (1);
	return (0);
}

void	read_inquotes(char **current, char *buffer, int *index)
{
	char	quote;

	quote = **current;
	buffer[(*index)++] = *(*current)++;
	while (**current && **current != quote)
	{
		buffer[(*index)++] = **current;
		(*current)++;
	}
	if (**current == quote)
		buffer[(*index)++] = *(*current)++;
}

int	check_open(t_val *tkn, char *arg, int pos)
{
	while (*arg)
	{
		if (*arg == '"')
		{
			(*tkn->tokens)[pos].quoted = 1;
			return (1);
		}
		arg++;
	}
	return (0);
}

int	delim_check(t_val *tkn, char *arg)
{
	int		index;
	char	*clean;
	char	*res;

	if (!tkn->expect_file || !*tkn->tokens)
		return (0);
	if ((*tkn->tokens)[*tkn->count - 1].type != T_OP)
		return (0);
	if (ft_strcmp((*tkn->tokens)[*tkn->count - 1].value, "<<") != 0)
		return (0);
	res = rmv_dquotes(arg);
	clean = ft_remove_qoats(res);
	index = *tkn->count - 1;
	(*tkn->tokens)[index].quoted = 0;
	if (arg && ft_strlen(arg) >= 2)
		check_open(tkn, arg, index);
	*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_FILE, clean);
	tkn->expect_file = 0;
	index = *tkn->count - 1;
	(*tkn->tokens)[index].empty_ex = 0;
	return (1);
}

char	*rmv_dquotes(char *arg)
{
	int		i;
	char	*cleaned;
	char	tmp[2];
	char	*new_str;

	i = 0;
	cleaned = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '$' && ((arg[i + 1] == '"' && arg[i + 2] == '"') || (arg[i
						+ 1] == '\'' && arg[i + 2] == '\'')))
		{
			i += 3;
			continue ;
		}
		tmp[0] = arg[i++];
		tmp[1] = '\0';
		new_str = ft_strjoin(cleaned, tmp);
		cleaned = new_str;
	}
	return (cleaned);
}
