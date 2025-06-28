/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:38:10 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 12:09:21 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*buffer_init(char *input)
{
	char	*buffer;

	buffer = ft_malloc(ft_strlen(input) + 2, 0x1);
	return (buffer);
}

void	initialize(char **current, char **buffer, char **arg)
{
	*buffer = buffer_init(*current);
	collect(current, *buffer);
	*arg = ft_strdup(*buffer);
}
