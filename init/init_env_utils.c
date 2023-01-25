/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:50:13 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 13:57:33 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*create_node(t_data *data, char *line, int alloc)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	is_error(data, node, MALLOC_ERR, 0);
	if (!alloc || !line)
		node -> line = line;
	else
	{
		node -> line = ft_strdup(line);
		is_error(data, node, MALLOC_ERR, 0);
		node -> alloc = 't';
	}
	return (node);
}

t_node	*ft_lst_add_front_s(t_node **node, t_node *new)
{
	if (!(*node))
		*(node) = new;
	else
	{
		new -> next = *(node);
		(*node)-> prev = new;
		(*node) = new;
	}
	return (new);
}

t_node	*ft_lstlast_s(t_node *lst)
{
	if (!(lst))
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
