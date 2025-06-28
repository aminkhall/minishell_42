/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:01:10 by mkhallou          #+#    #+#             */
/*   Updated: 2025/06/06 18:43:12 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(t_redir *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = -1;
	if (file->type == IN)
		fd = open(file->file, O_RDONLY, 0644);
	else if (file->type == OUT)
		fd = open(file->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (file->type == APPEND)
		fd = open(file->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

void	redir_null(void)
{
	int	dev_null;

	dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDOUT_FILENO);
	close(dev_null);
}

void	close_fd(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		++i;
	}
	return ;
}

void	close_fd_her(t_redir *file)
{
	t_redir	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->fd_herdoc != -1)
			close(tmp->fd_herdoc);
		tmp->fd_herdoc = -1;
		tmp = tmp->next;
	}
	return ;
}
