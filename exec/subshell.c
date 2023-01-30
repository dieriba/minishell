/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 02:39:29 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_shell_pipes(t_data *data)
{
	if (data -> subshell == 0 && data -> s_pipes_inited)
		close_one_end(data, data -> p_pipes, 1, &data -> s_pipes_inited);
	else if (data -> subshell == 1 && data -> s_pipes_inited)
	{
		close_one_end(data, data -> p_pipes, 1, &data -> s_pipes_inited);
		if (data -> s_pipes_inited == 2)
			data -> p_pipes[1] = data -> sub_pipes[0][1];
	}	
}

int	is_subshell(t_data *data, t_cmd **cmds, int *i, int subshell)
{
	if (cmds[(*i)]-> to_fork)
	{
		--cmds[(*i)]-> to_fork;
		--cmds[(*i)]-> p_open;
		data -> subshell_pid = fork();
		if (data -> subshell_pid == -1)
			print_err_and_exit(data, NULL, "bash89", 1);
		if (data -> subshell_pid == 0)
			executing(data, &cmds[(*i)], 1);
		++cmds[(*i)]-> p_open;
		if (subshell == 0)
			(*i) += end_cmd_par(&cmds[(*i)], subshell);
		else if (subshell == 1)
			(*i) += find_next_cmd(data, &cmds[(*i)]);
		handle_shell_pipes(data);
		return (1);
	}
	return (0);
}
