/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandingtwo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:13:48 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/05 12:29:18 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_d(char **res, char *input, int *i)
{
	int		start;
	int		len;
	char	*quoted;
	char	*joined;
	char	quote;

	quote = input[(*i)++];
	while (is_space(input[*i]))
		(*i)++;
	if (input[*i] == quote)
	{
		(*i)++;
		return ;
	}
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	len = *i - start;
	quoted = ft_substr(input, start, len);
	if (input[*i] == quote)
		(*i)++;
	joined = ft_strjoin(*res, quoted);
	*res = joined;
}

void	get_string(char **res, char *input, int *i)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = input[(*i)++];
	tmp[1] = '\0';
	joined = ft_strjoin(*res, tmp);
	*res = joined;
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
