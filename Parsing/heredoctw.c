/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoctw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:57:40 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/06 17:59:54 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files(char *tmp_filename, int fds[2])
{
	fds[0] = -1;
	fds[1] = -1;
	fds[0] = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	fds[1] = open(tmp_filename, O_RDONLY);
	unlink(tmp_filename);
	if (fds[0] < 0 || fds[1] < 0)
	{
		if (fds[0] >= 0)
			close(fds[0]);
		if (fds[1] >= 0)
			close(fds[1]);
		return (0);
	}
	return (1);
}

int	delimtter_check(char *line, char *delimiter, t_mini *var)
{
	if (!line)
	{
		var->status = 0;
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		var->status = 0;
		free(line);
		return (1);
	}
	return (0);
}

void	write_heredoc_line(char *line, int fd, int flag, t_mini *var)
{
	char	*expanded;

	if (flag == 1)
		write(fd, line, ft_strlen(line));
	else
	{
		expanded = expand_heredoc(line, var);
		write(fd, expanded, ft_strlen(expanded));
	}
	write(fd, "\n", 1);
}

int	heredoc_body(int fds[2], char *delimiter, t_mini *var, int flag)
{
	char	*line;

	if (exit_herdoc(0, 0) == 1)
		close(fds[1]);
	while (1 && exit_herdoc(0, 0) != 1)
	{
		signal(SIGINT, &herdoc_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (exit_herdoc(0, 0) == 1)
		{
			var->status = 130;
			close(fds[1]);
			free(line);
			return (0);
		}
		if (delimtter_check(line, delimiter, var))
			break ;
		write_heredoc_line(line, fds[0], flag, var);
		free(line);
	}
	return (1);
}

int	handle_heredoc(char *delimiter, int flag, t_mini *var)
{
	static int	heredoc_id = 0;
	char		*id_str;
	char		*tmp_filename;
	int			fds[2];
	int			tmp;

	tmp = flag;
	id_str = ft_itoa(heredoc_id++);
	if (!id_str)
		return (0);
	tmp_filename = ft_strjoin("/tmp/.minishell_heredoc_",
			ft_strjoin(ft_itoa_base(&tmp + *id_str), ".her"));
	if (!tmp_filename)
		return (0);
	if (!open_files(tmp_filename, fds))
		return (0);
	heredoc_body(fds, delimiter, var, flag);
	close(fds[0]);
	return (fds[1]);
}
