/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:20:30 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/06 19:15:58 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"  

int	exit_herdoc(int val, int flag)
{
	static int	ex;

	if (flag == 1)
		ex = val;
	return (ex);
}

void	herdoc_handler(int sig)
{
	(void) sig;
	exit_herdoc(1, 1);
	ioctl(0, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	return ;
}
