/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:12:57 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 22:27:21 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_files_tab(t_files **tab)
{
	int	len;

	len = -1;
	if (!tab)
		return (0);
	while (tab[++len])
		;
	return (len);
}

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

void	set_node(t_data *data, t_files **tab)
{
	int		len;
	t_doc	*node;

	len = len_files_tab(tab);
	while (len--)
	{
		if (tab[len]-> type == DOC)
		{
			node = ft_calloc(sizeof(t_doc), 1);
			is_error(data, node, MALLOC_ERR, 0);
			node -> limiter = tab[len]-> files;
			ft_lst_add_front_(&data -> here_docs, node);
		}
	}
}
