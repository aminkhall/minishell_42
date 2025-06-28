/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:03:44 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/15 17:40:31 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	res(int val, int flag)
{
	static int	c;

	if (flag == 1)
		c = val;
	return (c);
}

void	check_sig(int sig)
{
	if (sig == SIGINT)
	{
		res(1, 1);
		ft_putstr(1, "\n", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t'
			|| c == '\v'))
		return (true);
	return (false);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

void	remove_qu(char *s, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i];
			i++;
		}
		else if (quote && s[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			result[j++] = s[i++];
		}
	}
	result[j] = '\0';
}
