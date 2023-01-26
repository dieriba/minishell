/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 05:36:27 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 03:57:34 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_here_doc(t_data *data, t_doc **head)
{
	t_doc	*node;
	t_doc	*next;

	node = *head;
	while (node)
	{
		close_fd(data, "bash1", &node -> pipes[0]);
		close_fd(data, "bash2", &node -> pipes[1]);
		next = node -> next;
		ft_free_elem((void **)&node);
		node = next;
	}
	(*head) = NULL;
}

void	clean_struct(t_data *data)
{
	data -> prev_pipes = -1;
	data -> last_exec_stat = 0;
	data -> inited = 0;
	free_cmd(data -> cmds);
	ft_free_elem((void **)&g_collector);
	ft_free_elem((void **)&data -> cp_to_parse);
	clean_here_doc(data, &data -> here_docs);
}
