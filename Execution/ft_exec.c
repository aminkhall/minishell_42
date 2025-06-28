/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:01:17 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/12 15:27:23 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_process(t_mini *mini, int (*pipes)[2], int i)
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (mini->cmd_count > 1)
	{
		if (i == 0)
			dup2(pipes[0][1], STDOUT_FILENO);
		else if (i == mini->cmd_count - 1)
			dup2(pipes[mini->cmd_count - 2][0], STDIN_FILENO);
		else
		{
			dup2(pipes[i - 1][0], STDIN_FILENO);
			dup2(pipes[i][1], STDOUT_FILENO);
		}
	}
	close_all_pipes(pipes, mini->cmd_count);
	ft_redir(mini->cmd->redirs, 0, &mini->status);
	if (!mini->cmd->args[0])
		(close_fd(), ft_malloc(0, 0), exit(0));
	if (!is_builtins(mini->cmd->args))
	{
		exec_builtins(&mini->env, mini->cmd->args, &mini->status);
		(ft_malloc(0, 0), exit(mini->status));
	}
	ft_execve(mini);
}

void	single_bultin(t_env **lst, t_cmd *cmd, int *status)
{
	int	fd1;
	int	fd2;

	fd1 = dup(STDIN_FILENO);
	fd2 = dup(STDOUT_FILENO);
	ft_redir(cmd->redirs, 1, status);
	if (cmd->redirs && *status == 1)
		*status = 1;
	else if (cmd->redirs && *status != 130)
		exec_builtins(lst, cmd->args, status);
	else if (!cmd->redirs)
		exec_builtins(lst, cmd->args, status);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(fd1);
	close(fd2);
}

static int	fork_and_setup_signal(pid_t *pids, int i)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pids[i] = fork();
	if (pids[i] == -1)
		return (1);
	return (0);
}

static int	spawn_processes(t_mini *mini, pid_t *pids, int pipes[][2])
{
	int		i;
	t_redir	*tmp;

	i = 0;
	while (i < mini->cmd_count)
	{
		tmp = mini->cmd->redirs;
		pids[i] = -1;
		if (mini->cmd_count == 1 && !is_builtins(mini->cmd->args))
		{
			single_bultin(&mini->env, mini->cmd, &mini->status);
			break ;
		}
		else
		{
			if (fork_and_setup_signal(pids, i))
				return (1);
			if (pids[i] == 0)
				handle_child_process(mini, pipes, i);
		}
		close_fd_her(tmp);
		mini->cmd = mini->cmd->next;
		i++;
	}
	return (1);
}

int	ft_exec(t_mini *mini)
{
	pid_t	*pids;
	int		code;
	int		(*pipes)[2];

	if (!mini || !mini->cmd)
	{
		mini->status = 0;
		return (0);
	}
	pids = ft_malloc(sizeof(pid_t) * mini->cmd_count, 1);
	pipes = ft_malloc(sizeof(int [2]) * (mini->cmd_count - 1), 1);
	init_pipes(pipes, mini->cmd_count);
	if (!spawn_processes(mini, pids, pipes))
		return (0);
	close_all_pipes(pipes, mini->cmd_count);
	wait_for_children(pids, mini->cmd_count, &mini->status);
	if (WIFEXITED(mini->status))
	{
		code = WEXITSTATUS(mini->status);
		mini->status = code;
	}
	return (1);
}
