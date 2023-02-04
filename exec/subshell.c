/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/04 03:00:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_subshell(t_data *data, t_cmd **cmds, int *i, int subshell)
{
	if (cmds[(*i)]-> to_fork)
	{
		--cmds[(*i)]-> to_fork;
		--cmds[(*i)]-> p_open;
		data -> subshell++;
		data -> subshell_pid = fork();
		cmds[(*i)]-> pid = data -> subshell_pid;
		if (data -> subshell_pid == -1)
			print_err_and_exit(data, NULL, "bash89", 1);
		if (data -> subshell_pid == 0)
			executing(data, &cmds[(*i)], 1);
		data -> subshell--;
		++cmds[(*i)]-> p_open;
		if (subshell == 0)
			(*i) += end_cmd_par(&cmds[(*i)], subshell);
		else if (subshell == 1)
			(*i) += find_next_cmd(data, &cmds[(*i)]);
		return (1);
	}
	return (0);
}
