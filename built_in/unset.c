/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:05:39 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 22:36:05 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_env *env)
{
	t_node	*prev;

	prev = env -> last -> prev;
	env -> last -> prev = NULL;
	prev -> next = NULL;
	env -> last = prev;
}
