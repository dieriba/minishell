/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:36:50 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 00:40:58 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*find_(t_data *data, char *line)
{
	t_node	*node;

	node = data -> alias -> head;
	while (node)
	{
		if (!check(node -> line, line))
			return (node);
		node = node -> next;
	}
	return (NULL);
}

void	remove_alias(t_data *data, t_node *node)
{
	if (node -> prev)
		node -> prev -> next = node -> next;
	if (node -> next)
		node -> next -> prev = node -> prev;
	if (node == data -> alias -> head)
		data -> alias -> head = node -> next;
	if (node == data -> alias -> last)
		data -> alias -> last = node -> prev;
	ft_free_elem((void **)&node -> line);
	ft_free_elem((void **)&node);
	data -> status = 0;
}

void	unalias(t_cmd *cmd)
{
	size_t	i;
	t_node	*node;

	i = 0;
	while (cmd -> args[++i])
	{
		node = find_(cmd -> data, cmd -> args[i]);
		if (node == NULL)
			continue ;
		remove_alias(cmd -> data, node);
	}
}
