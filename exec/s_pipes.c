/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:13:41 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/06 21:30:02 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_write_pipes(t_s_pipes *head)
{
	t_s_pipes	*node;
	int			fd;

	fd = -1;
	if (head == NULL)
		return (-1);
	node = head;
	if (head -> s_pipes[1] > 0)
		return (head -> s_pipes[1]);
	node = head -> next;
	while (node)
	{
		if (node -> s_pipes[1] > 0)
			fd = node -> s_pipes[1];
		node = node -> next;
	}
	return (fd);
}

int	find_read_pipes(t_s_pipes *head, int subshell)
{
	t_s_pipes	*node;

	node = head;
	while (node)
	{
		if (subshell == node -> subshell[0])
			return (node -> s_pipes[0]);
		node = node -> next;
	}
	return (-1);
}

void	clean_s_pipes(t_data *data)
{
	t_s_pipes	*node;
	t_s_pipes	*next;

	node = data -> s_pipes;
	while (node)
	{
		next = node -> next;
		close_fd(data, "bash", &node -> s_pipes[0]);
		close_fd(data, "bash", &node -> s_pipes[1]);
		free(node);
		node = next;
	}
	data -> s_pipes = 0;
}
