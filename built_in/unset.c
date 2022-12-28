/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:05:39 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 23:41:52 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_node(t_env *env, t_node *node, char alloc)
{
	if (node -> prev == NULL)
	{
		env -> start = node -> next;
		node -> next = NULL;
	}
	else if (node -> next == NULL)
	{
		env -> last = node -> prev;
		node -> prev = NULL;
	}
	else
	{
		node -> prev -> next = node -> next;
		node -> next -> prev = node -> prev;
		node -> next = NULL;
		node -> prev = NULL;
	}
	free(node);
	if (alloc)
		free(node -> line);
}

void	unset(t_env *env, char *to_find)
{
	t_node	*var;

	var = find_var(env -> data, to_find);
	if (var == NULL)
		return ;
	remove_node(env, var, var -> alloc);
}
