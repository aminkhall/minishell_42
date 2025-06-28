/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:59:28 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/16 15:04:49 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_expand(char *input)
{
	int	count;

	count = 0;
	while (*input && *input != '$')
		input++;
	while (*input == '$')
	{
		count++;
		input++;
	}
	return (count % 2 != 0);
}

int	check_heredoc(char **current)
{
	if (!current || !*current)
		return (0);
	while (**current)
	{
		if ((*current)[0] == '<' && (*current)[1] == '<')
		{
			*current += 2;
			return (1);
		}
		(*current)++;
	}
	return (0);
}

int	has_space(char *str)
{
	while (is_space(*str))
		str++;
	while (*str)
	{
		if (is_space(*str))
		{
			return (1);
		}
		str++;
	}
	return (0);
}

void	quote_back(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		set_back_qoats(s[i]);
		i++;
	}
}

void	new_node(t_cmd *head)
{
	while (head)
	{
		quote_back(head->args);
		head = head->next;
	}
}
