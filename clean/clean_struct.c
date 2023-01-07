/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 05:36:27 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/07 20:24:01 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_here_doc(t_doc **head)
{
	t_doc	*node;
	t_doc	*next;
	
	node = *head;
	while (node)
	{
		next = node -> next;
		free(node);
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
	free(data -> cp_to_parse);
	clean_here_doc(&data -> here_docs);
	if (data -> here_doc_opened && data -> here_doc_closed == 0)
		close_all_pipes(data, &data -> here_docs);
	data -> here_doc_closed = 0;
	data -> here_doc_opened = 0;
}
