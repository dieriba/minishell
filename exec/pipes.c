/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:28:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/15 12:28:57 by dtoure           ###   ########.fr       */
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

void	close_all_pipes(t_data *data, t_doc **head, int read_, int write_)
{
	t_doc	*node;

	node = (*head);
	while (node)
	{
		if (read_)
			close_fd(data, "bash", node -> pipes[0]);
		if (write_)
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

void	close_both_pipes(t_data *data, int pipes[2], int *inited)
{
	if ((*inited))
	{
		close_fd(data, "bash", pipes[0]);
		close_fd(data, "bash", pipes[1]);
		(*inited) -= 1;
	}
}

void	init_pipes(t_data *data, int pipes[2], int *inited, int s_pipes)
{
	if (pipe(pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 1);
	if (s_pipes)
		data -> p_pipes = pipes;
	(*inited) += 1;
}