/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:39:42 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 17:19:22 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand(char *input, t_mini *cmd)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (input[i])
	{
		get_env(&res, input, &i, cmd);
		break ;
	}
	return (res);
}

char	*expand_her(char *input, t_mini *cmd)
{
	char	*res;
	int		i;
	int		in_s;
	int		in_d;

	res = ft_strdup("");
	i = 0;
	in_s = 0;
	in_d = 0;
	while (input[i])
	{
		i++;
		if (input[i] == '\'' || input[i] == '"')
			empty_d(&res, input, &i);
		else
		{
			get_env_heredoc(&res, input, &i, cmd);
			break ;
		}
	}
	return (res);
}

char	**expand_export(char *input, t_mini *cmd)
{
	char	*str;
	char	**out;

	str = expand(input, cmd);
	if (!*str)
	{
		out = ft_malloc(sizeof(char *) * 2, 0x1);
		out[0] = ft_strdup("");
		out[1] = NULL;
		return (out);
	}
	return (split_rs(str));
}

char	*expand_variable(char *value, t_mini *cmd)
{
	return (expand(value, cmd));
}

char	*expand_heredoc(char *value, t_mini *cmd)
{
	return (expand_her(value, cmd));
}
