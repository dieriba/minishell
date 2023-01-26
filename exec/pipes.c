/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:28:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 03:54:46 by dtoure           ###   ########.fr       */
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
			close_fd(data, "bash9", &node -> pipes[0]);
		if (write_)
			close_fd(data, "bash10", &node -> pipes[1]);
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
		close_fd(data, "bash11", &pipes[0]);
		close_fd(data, "bash12", &pipes[1]);
		(*inited) -= 2;
	}
}

void	init_pipes(t_data *data, int pipes[2], int *inited, int s_pipes)
{
	if (pipe(pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 1);
	if (s_pipes)
		data -> p_pipes = pipes;
	(*inited) += 2;
}

void	close_one_end(t_data *data, int *pipes, int i, int *inited)
{
	if ((*inited))
	{
		if (pipes[i] != -1)
			close_fd(data, "bash13", &pipes[i]);
		(*inited) -=1;
	}
}

void	close_sub_pipes(t_data *data, int subshell)
{
	static int sub = -1;
	if (subshell == 0)
		return ;
	data -> subshell = subshell + (++sub);
	if (data -> s_pipes_inited == 2)
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	else if (data -> s_pipes_inited == 3)
	{
		close_one_end(data, data -> sub_pipes[0], 0, &data -> s_pipes_inited);
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	}
}