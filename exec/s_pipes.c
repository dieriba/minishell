/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:13:41 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 15:30:51 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_s_pipes(t_data *data)
{
	t_s_pipes	*node;
	t_s_pipes	*next;

	node = data -> s_pipes;
	while (node)
	{
		next = node -> next;
		close_fd(data, "bash", &node -> s_pipes[0]);
		close_fd(data, "bash", &node -> s_pipes[1]);
		free(node);
		node = next;
	}
	data -> s_pipes = 0;
}
