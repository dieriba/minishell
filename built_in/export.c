/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:30:18 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 23:26:50 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_data *data, t_node *prev_last, char *new_var)
{
	t_node	*new_last;

	new_last = create_node(new_var, 't');
	is_error(data, new_last, MALLOC_ERR);
	prev_last -> next = new_last;
	new_last -> prev = prev_last;
	data -> env -> last = new_last;
}
