/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:50:13 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 21:35:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*create_node(t_data *data, char *line, int alloc)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node), 1);
	is_error(data, node, MALLOC_ERR, 1);
	if (!alloc || !line)
		node -> line = line;
	else
	{
		node -> line = ft_strdup(line);
		is_error(data, node, MALLOC_ERR, 1);
		node -> alloc = 't';
	}
	return (node);
}

t_node	*ft_lst_add_front_s(t_data *data, t_node **node, t_node *new)
{
	if (!(*node))
	{
		*(node) = new;
		if (data)
			data -> env -> last = new;
	}
	else
	{
		new -> next = *(node);
		(*node)-> prev = new;
		(*node) = new;
	}
	return (new);
}

void	create_list(t_data *data, char **envp)
{
	t_node	*node;
	int		i;

	i = ft_tab_len(envp);
	i--;
	while (i > -1)
	{
		node = create_node(data, envp[i], 0);
		is_error(data, node, MALLOC_ERR, 1);
		ft_lst_add_front_s(data, &data -> env -> start, node);
		i--;
	}
}

t_node	*ft_lstlast_s(t_node *lst)
{
	if (!(lst))
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
