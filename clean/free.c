/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:32:53 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 20:44:00 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i] -> args)
			ft_free_tab(cmds[i] -> args);
		if (cmds[i] -> in)
			ft_free_tab(cmds[i] -> in);
		if (cmds[i] -> out)
			ft_free_tab(cmds[i] -> out);
		if (cmds[i] -> in_here_doc)
			ft_free_tab(cmds[i] -> in_here_doc);
		if (cmds[i] -> out_append)
			ft_free_tab(cmds[i] -> out_append);
		free(cmds[i]);
	}
	free(cmds);
}

void	free_list(t_line **head)
{
	t_line	*next;
	t_line	*node;

	node =  (*head);
	while (node)
	{
		free(node -> line);
		node -> line = NULL;
		next = node -> next;
		node -> next = NULL;
		node -> prev = NULL;
		free(node);
		node = next;
	}
	(*head) = NULL;
}