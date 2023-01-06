/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:46:00 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/06 15:29:37 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lst_add_front_(t_doc **node, t_doc *new)
{
	if (!(*node))
		*(node) = new;
	else
	{
		new -> next = *(node);
		(*node)-> prev = new;
		(*node) = new;
	}
}

int	tab_len(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

void	set_node(t_data *data, char **limiter)
{
	int		len;
	t_doc	*node;
	
	len = ft_tab_len(limiter);
	while (len--)
	{
		node = ft_calloc(sizeof(t_doc), 1);
		is_error(data, node, MALLOC_ERR, 0);
		node -> limiter = limiter[len];
		ft_lst_add_front_(&data -> here_docs, node);
	}
}

void	open_here_doc(t_data *data, t_cmd **cmds)
{
	int	len;
	int	i;

	i = -1;
	len = tab_len(data -> cmds);
	while (--len > -1)
	{
		if (cmds[len]-> in_here_doc)
			set_node(data, cmds[len]-> in_here_doc);
	}
}

void	fork_docs(t_data *data, )