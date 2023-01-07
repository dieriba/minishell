/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:28:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/07 20:28:29 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_pipes(t_data *data, t_doc **head)
{
	t_doc	*node;

	node = (*head);
	if ((*head) == NULL)
		return (1);
	while (node)
	{
		if (pipe(node -> pipes) < 0)
			print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
		node = node -> next;
	}
	data -> here_doc_opened = 1;
	g_collector = ft_calloc(sizeof(t_collector), 1);
	is_error(data, g_collector, MALLOC_ERR, 0);
	g_collector -> data = data;
	return (0);
}

void	close_all_pipes(t_data *data, t_doc **head)
{
	t_doc	*node;
	
	node = (*head);
	while (node)
	{
		close_fd(data, "bash", node -> pipes[0]);
		close_fd(data, "bash", node -> pipes[1]);
		node = node -> next;
	}
}

int	find_fd(t_doc *node, char *limiter)
{
	while (node)
	{
		if (node -> limiter == limiter)
			break ;
		node = node -> next;
	}
	return (node -> pipes[0]);
}