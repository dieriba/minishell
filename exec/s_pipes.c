/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:13:41 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 12:04:03 by dtoure           ###   ########.fr       */
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
		close_fd(data, "minishell", &node -> s_pipes[0]);
		close_fd(data, "minishell", &node -> s_pipes[1]);
		free(node);
		node = next;
	}
	data -> s_pipes = 0;
}

void	set_in_pipes(t_cmd **cmds, t_s_pipes *node)
{
	int			i;
	int			p_num;

	i = 0;
	p_num = 0;
	cmds[i]-> write_end = node;
	while (cmds[++i])
	{
		p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
		cmds[i]-> read_end = node;
		if (p_num == 0)
			break ;
	}
}

void	set_out_pipes(t_cmd **cmds, t_s_pipes *node)
{
	int			i;
	int			p_num;

	i = -1;
	p_num = 0;
	while (cmds[++i])
	{
		p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
		cmds[i]-> write_end = node;
		if (p_num == 0)
			break ;
	}
	cmds[++i]-> read_end = node;
	if (cmds[i]-> p_open)
	{
		p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
		while (cmds[++i])
		{
			p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
			cmds[i]-> read_end = node;
			if (p_num == 0)
				break ;
		}
	}
}

void	init_s_pipes(t_cmd **cmds, int i, int in_pipe, int out_pipe)
{
	t_s_pipes	*node;
	t_data		*data;

	if (in_pipe && out_pipe)
		return ;
	data = cmds[0]-> data;
	node = ft_calloc(sizeof(t_s_pipes), 1);
	is_error(data, node, MALLOC_ERR, 0);
	if (pipe(node -> s_pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
	if (in_pipe == 0 && cmds[i + 1]-> p_open)
		set_in_pipes(&cmds[i], node);
	else if (out_pipe == 0 && cmds[i]-> p_open)
		set_out_pipes(&cmds[i], node);
	if (data -> s_pipes == NULL)
		data -> s_pipes = node;
	else
	{
		node -> next = data -> s_pipes;
		data -> s_pipes = node;
	}
}
