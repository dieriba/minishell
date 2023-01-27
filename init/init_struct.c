/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:39:54 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 04:40:20 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data **data)
{
	(*data) = ft_calloc(sizeof(t_data), 1);
	is_error((*data), (*data), MALLOC_ERR, 1);
	(*data)-> neg_single_start = '\'' * -1;
	(*data)-> neg_single_end = '\'' * -2;
	(*data)-> neg_double_start = '"' * -1;
	(*data)-> neg_double_end = '"' * -2;
	(*data)-> prev_pipes = -1;
	(*data)-> cp_to_parse = NULL;
	handle_signals((*data));
}

void	set_default_data(t_data *data, int len)
{
	int	j;

	j = -1;
	while (++j < len)
	{
		data -> cmds[j] = ft_calloc(sizeof(t_cmd), 1);
		is_error(data, data -> cmds, MALLOC_ERR, 1);
		data -> cmds[j]-> data = data;
		data -> cmds[j]-> index = j + 1;
		if (j > 0)
			data -> cmds[j]-> prev_cmd = data -> cmds[j - 1];
	}
}
