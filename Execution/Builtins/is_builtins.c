/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:13 by mkhallou          #+#    #+#             */
/*   Updated: 2025/05/31 16:12:28 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtins(char **input)
{
	if (!input || !(*input) || !(**input))
		return (1);
	if (!ft_strncmp(*input, "echo", 5))
		return (0);
	else if (!ft_strncmp(*input, "cd", 3))
		return (0);
	else if (!ft_strncmp(*input, "pwd", 4))
		return (0);
	else if (!ft_strncmp(*input, "unset", 6))
		return (0);
	else if (!ft_strncmp(*input, "export", 7))
		return (0);
	else if (!ft_strncmp(*input, "env", 4))
		return (0);
	else if (!ft_strncmp(*input, "exit", 5))
		return (0);
	return (1);
}

int	exec_builtins(t_env **env, char **input, int *status)
{
	static char	*pwd;
	char		*tmp;

	if (!input || !(*input) || !(**input))
		return (1);
	tmp = get_value(env, "PWD");
	if (tmp)
		pwd = ft_strdup(tmp);
	if (!ft_strncmp(*input, "echo", 5))
		*status = ft_echo(++input);
	else if (!ft_strncmp(*input, "cd", 3))
		*status = ft_cd(env, ++input, pwd);
	else if (!ft_strncmp(*input, "pwd", 4))
		*status = ft_pwd(pwd);
	else if (!ft_strncmp(*input, "unset", 6))
		*status = ft_unset(env, (++input));
	else if (!ft_strncmp(*input, "export", 7))
		*status = ft_export(env, (++input));
	else if (!ft_strncmp(*input, "env", 4))
		*status = ft_env(env);
	else if (!ft_strncmp(*input, "exit", 5))
		ft_exit(++input, status);
	else
		return (1);
	return (0);
}
