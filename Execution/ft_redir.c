/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:32:06 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/16 15:37:24 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_ambiguous(t_redir *file, int flag, int *status)
{
	if (flag && file->ambiguous)
	{
		perror("Ambiguous redirect");
		redir_null();
		*status = 1;
	}
	else if (!flag && file->ambiguous)
	{
		perror("Ambiguous redirect");
		*status = 1;
		(ft_malloc(0, 0), exit(1));
	}
}

int	handle_file_redir(t_redir *file, int flag, int *status)
{
	int	fd;

	fd = ft_open(file);
	if (fd == -1)
	{
		perror(file->file);
		if (flag)
		{
			redir_null();
			*status = 1;
			return (0);
		}
		else
		{
			*status = 1;
			(close_fd(), ft_malloc(0, 0), exit(1));
		}
	}
	if (file->type == IN)
		dup2(fd, STDIN_FILENO);
	else if (file->type == OUT || file->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	ft_handle_heredoc(t_redir *file, int flag, int *status)
{
	int	fd;

	fd = file->fd_herdoc;
	if (fd != -1)
		dup2(fd, STDIN_FILENO);
	close(file->fd_herdoc);
	if (flag && *status == 130)
		return ;
	else if (!flag && *status == 130)
		(ft_malloc(0, 0), exit(130));
}

void	ft_redir(t_redir *file, int flag, int *status)
{
	int	continue_loop;

	if (!file)
		return ;
	continue_loop = 1;
	while (file && continue_loop)
	{
		if (file->ambiguous)
		{
			handle_ambiguous(file, flag, status);
			if (flag)
				break ;
		}
		else if (file->type == HEREDOC)
		{
			ft_handle_heredoc(file, flag, status);
			if (*status == 130)
				break ;
		}
		else
			continue_loop = handle_file_redir(file, flag, status);
		file = file->next;
	}
	return ;
}
