/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:58:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 17:01:39 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	collect(char **current, char *buffer)
{
	int	index;
	int	was_quoted;

	index = 0;
	was_quoted = 0;
	while (**current && !is_space(**current) && !is_operator(**current))
	{
		if (is_quote(**current))
		{
			was_quoted = 1;
			read_inquotes(current, buffer, &index);
		}
		else
			buffer[index++] = *(*current)++;
	}
	buffer[index] = '\0';
	return (was_quoted);
}

char	*expand_var(t_val *tkn, char *arg, t_mini *cmd)
{
	int		current_index;
	char	*tmp;

	tmp = expand_variable(arg, cmd);
	current_index = *tkn->count - 1;
	if (!tmp || !*tmp)
	{
		(*tkn->tokens)[current_index].empty_ex = 1;
		(*tkn->tokens)[current_index].ambiguous = 1;
	}
	if (tmp)
	{
		(*tkn->tokens)->expanded = 1;
		if (has_space(tmp) && tkn->expect_file)
			(*tkn->tokens)[current_index].ambiguous = 1;
		arg = tmp;
	}
	else
		arg = ft_strdup("");
	return (arg);
}

int	expand_exprt(t_val *tkn, char *arg, t_mini *cmd)
{
	int		current_index;
	char	**expanded;
	char	*clean;

	expanded = expand_export(arg, cmd);
	if (!expanded || !*expanded)
	{
		clean = ft_strdup("");
		*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_ARG, clean);
		return (1);
	}
	while (*expanded)
	{
		clean = ft_remove_qoats(*expanded);
		if (tkn->expect_file)
			*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_FILE, clean);
		else
			*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_ARG, clean);
		current_index = *tkn->count - 1;
		(*tkn->tokens)[current_index].expanded = 1;
		if (ft_strlen(*expanded) == 0)
			(*tkn->tokens)[current_index].empty_ex = 1;
		expanded++;
	}
	return (1);
}

void	token_cases(t_val *tkn, char *arg)
{
	char	*clean_arg;
	int		i;

	clean_arg = ft_remove_qoats(arg);
	i = 0;
	if (tkn->expect_file)
	{
		while (is_space(clean_arg[i]))
			i++;
		clean_arg = ft_substr(clean_arg, i, ft_strlen(clean_arg));
		*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_FILE, clean_arg);
		tkn->expect_file = 0;
	}
	else if (tkn->expect_cmd)
	{
		*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_CMD, clean_arg);
		tkn->expect_cmd = 0;
		if (ft_strcmp(clean_arg, "export") == 0)
			tkn->to_export = 1;
	}
	else
		*tkn->tokens = add_token(*tkn->tokens, tkn->count, T_ARG, clean_arg);
}

void	collect_argument(char **current, t_val *tkn, t_mini *cmd)
{
	char	*buffer;
	char	*arg;
	int		current_index;

	initialize(current, &buffer, &arg);
	if (delim_check(tkn, arg))
		return ;
	if (ft_strchr(arg, '$'))
	{
		if (should_expand_var(arg, tkn))
		{
			if (expand_exprt(tkn, arg, cmd))
				return ;
		}
		else
			arg = expand_var(tkn, arg, cmd);
	}
	token_cases(tkn, arg);
	current_index = *tkn->count - 1;
	(*tkn->tokens)[current_index].empty_ex = 0;
}
