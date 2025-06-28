/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:43:47 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/06 17:42:07 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_heredocs(t_token *tmp)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (tmp[i].type != T_END)
	{
		if (tmp[i].type == T_OP && ft_strcmp(tmp[i].value, "<<") == 0)
			counter++;
		i++;
	}
	return (counter);
}

int	count_args(t_token *tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start].type != T_END
		&& !(tokens[start].type == T_OP
			&& ft_strcmp(tokens[start].value, "|") == 0))
	{
		if (tokens[start].type == T_ARG || tokens[start].type == T_CMD)
			count++;
		start++;
	}
	return (count);
}

void	add_exp(t_cmd **list, int expanded)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = ft_malloc(sizeof(t_cmd), 0x1);
	if (!new)
		return ;
	new->expanded = expanded;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	is_quoted(char *str)
{
	size_t	len;
	char	first;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	first = *str;
	if (len < 2)
		return (0);
	return (first == str[len - 1] && (first == '\'' || first == '"'));
}

void	add_heredoc(t_redir **list, t_rtype type, char *filename, int fd_herdoc)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_malloc(sizeof(t_redir), 0x1);
	if (!new)
		return ;
	new->type = type;
	new->file = filename;
	new->next = NULL;
	new->ambiguous = 0;
	new->fd_herdoc = fd_herdoc;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
