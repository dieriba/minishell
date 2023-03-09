/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:39:54 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/09 04:12:37 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	directory(t_data *data)
{
	static int	status = -1;
	char		*path;
	char		*tmp;

	tmp = data -> curr_dir.pwd;
	path = data -> curr_dir.path;
	if ((!data -> status && data -> status != status)
		|| status == -1 || data -> curr_dir.new_dir)
	{
		data -> curr_dir.pwd = ft_strjoin(
				GREEN"➜ "RESET_COLOR CYAN, path, " "RESET_COLOR, 1);
		ft_free_elem((void **)&tmp);
	}
	else if (data -> status && status != data -> status)
	{
		(data -> curr_dir.pwd) = ft_strjoin(
				RED"➜ "RESET_COLOR CYAN, path, " "RESET_COLOR, 1);
		ft_free_elem((void **)&tmp);
	}
	is_error(data, data -> curr_dir.pwd, MALLOC_ERR, 0);
	data -> curr_dir.new_dir = 0;
	status = data -> status;
}

void	init_struct(t_data **data)
{
	(*data) = ft_calloc(sizeof(t_data), 1);
	is_error((*data), (*data), MALLOC_ERR, 0);
	(*data)-> alias = ft_calloc(sizeof(t_alias), 1);
	is_error((*data), (*data)-> alias, MALLOC_ERR, 0);
	(*data)-> curr_dir.dir_name = getcwd(NULL, 0);
	is_error(*data, (*data)-> curr_dir.dir_name, "minishell", 1);
	(*data)-> curr_dir.path = ft_strrchr((*data)-> curr_dir.dir_name, '/') + 1;
	(*data)-> prev_pipes = -1;
	handle_signals();
}

void	set_default_data(t_data *data, int len)
{
	int	j;

	j = -1;
	while (++j < len)
	{
		data -> cmds[j] = ft_calloc(sizeof(t_cmd), 1);
		is_error(data, data -> cmds[j], MALLOC_ERR, 1);
		data -> cmds[j]-> data = data;
		if (j > 0)
			data -> cmds[j]-> prev_cmd = data -> cmds[j - 1];
	}
}
