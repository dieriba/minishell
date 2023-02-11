/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:28:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 13:02:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_pipes(t_data *data, t_doc **head, int read_, int write_)
{
	t_doc	*node;

	node = (*head);
	while (node)
	{
		if (read_)
			close_fd(data, "bash", &node -> pipes[0]);
		if (write_)
			close_fd(data, "bash", &node -> pipes[1]);
		node = node -> next;
	}
}

void	close_both_pipes(t_data *data, int pipes[2], int *inited)
{
	if (*inited)
	{
		close_fd(data, "bash", &pipes[0]);
		close_fd(data, "bash", &pipes[1]);
		(*inited) -= 2;
	}
}

void	init_pipes(t_data *data, int pipes[2], int *inited)
{
	if (pipe(pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 1);
	(*inited) += 2;
}

void	handle_pipes(t_data *data, t_cmd *cmd)
{
	if (data -> s_pipes && data -> prev_pipes == -1
		&& !ft_strcmp(cmd -> prev_stop, "|"))
		close_fd(data, "bash", &cmd -> read_end -> s_pipes[0]);
	close_fd(data, "bash error", &data -> prev_pipes);
	if (data -> inited)
	{
		data -> prev_pipes = data -> pipes[0];
		close_fd(data, "bash pipes close", &data -> pipes[1]);
	}
	data -> inited = 0;
}
