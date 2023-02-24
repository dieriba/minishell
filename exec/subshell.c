/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:33:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_base_setup(t_cmd *cmd)
{
	if (cmd -> p_open && !cmd -> to_fork)
		cmd -> p_open = 1;
	else if (cmd-> p_open)
		cmd -> p_open = cmd -> to_fork;
	cmd -> executed = 1;
}

int	is_subshell(t_data *data, t_cmd **cmds, int *i)
{
	int		j;

	if (cmds[(*i)]-> to_fork)
	{
		j = end_cmd_par(cmds, *i);
		if (cmds[j] && cmds[j + 1])
			cmds[j + 1]-> break_cmd = 1;
		--cmds[(*i)]-> to_fork;
		data -> subshell++;
		data -> subshell_pid = fork();
		cmds[(*i)]-> pid = data -> subshell_pid;
		if (data -> subshell_pid == -1)
			print_err_and_exit(data, NULL, "minishell", 1);
		if (data -> subshell_pid == 0)
			executing(data, &cmds[(*i)]);
		data -> subshell--;
		(*i) = j;
		if (cmds[j] && cmds[j + 1])
			cmds[j + 1]-> break_cmd = 0;
		close_fd(data, "minishell", &data -> prev_pipes);
		return (1);
	}
	return (0);
}
