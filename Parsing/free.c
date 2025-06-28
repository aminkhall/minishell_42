/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:20:19 by aymisbah          #+#    #+#             */
/*   Updated: 2025/06/03 21:17:34 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_delete	*last_cmd(t_delete *lst)
{
	t_delete	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_front(t_delete **head, t_delete *node)
{
	node->next = (*head);
	(*head) = node;
}

void	add_back(t_delete **head, t_delete *node)
{
	if (!head || !node)
		return ;
	if (*head == NULL)
		add_front(head, node);
	else
		last_cmd(*head)->next = node;
	node->next = NULL;
}

void	free_list(t_delete **head)
{
	t_delete	*current;
	t_delete	*next;

	current = *head;
	while (current != NULL)
	{
		if (current->ptr)
			free(current->ptr);
		next = current->next;
		free (current);
		current = next;
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, int flag)
{
	static t_delete		*val;
	void				*str;

	str = NULL;
	if (flag == 1)
	{
		str = malloc(size);
		if (str == NULL)
			return (NULL);
		else
			add_back(&val, lstnew(str));
	}
	else
		free_list(&val);
	return (str);
}
