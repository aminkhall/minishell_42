/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:27:46 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/12 15:27:46 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(pid_t *pids, int cmd_count, int *status)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], status, 0);
		if (WIFSIGNALED(*status))
		{
			if (WTERMSIG(*status) == SIGINT)
				(write(1, "\n", 1), *status = 130);
			else if (WTERMSIG(*status) == SIGQUIT)
				(write(1, "Quit\n", 6), *status = 131);
		}
		++i;
	}
}

char	*ft_getnewpath(char *av, char *new_path)
{
	char	*tmp_path;
	char	**dir;
	int		i;

	if (!new_path)
		return (ft_strdup(av));
	dir = ft_split(new_path, ':');
	if (!dir)
		return (NULL);
	i = 0;
	while (dir && dir[i])
	{
		tmp_path = ft_join(dir[i], "/");
		new_path = ft_join(tmp_path, av);
		if (!access(new_path, F_OK | X_OK))
			break ;
		++i;
		new_path = NULL;
	}
	return (new_path);
}

char	*ft_getpath(t_env **env, char *av)
{
	char	*new_path;
	char	*tmp_path;

	new_path = NULL;
	tmp_path = NULL;
	if (!av)
		return (NULL);
	if (ft_strchr(av, '/'))
		new_path = ft_strdup(av);
	else
	{
		tmp_path = get_value(env, "PATH");
		new_path = ft_getnewpath(av, tmp_path);
	}
	return (new_path);
}

void	ft_execve(t_mini *mini)
{
	char	*new_path;
	char	*str;
	char	**tab;

	new_path = ft_getpath(&mini->env, mini->cmd->args[0]);
	tab = arr_env(mini->env);
	if (!new_path || execve(new_path, mini->cmd->args, tab) == -1)
	{
		if (errno == ENOENT || mini->cmd->args[0][0] == '\0')
		{
			str = ft_join(mini->cmd->args[0], ": command not found\n");
			(write(2, str, ft_strlen(str)), ft_malloc(0, 0), exit(127));
		}
		else if (errno == EACCES)
		{
			str = ft_join(mini->cmd->args[0], ": Permission denied\n");
			(write(2, str, ft_strlen(str)), ft_malloc(0, 0), exit(126));
		}
		else if (access(mini->cmd->args[0], X_OK) != 0)
			(perror(mini->cmd->args[0]), ft_malloc(0, 0), exit(126));
		else
			exit(0);
	}
}
