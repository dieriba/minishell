/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/12 14:30:05 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_subshell(t_data *data, t_cmd **cmds, int *i, int subshell)
{
	int	status;

	status = 0;
	if (cmds[(*i)]-> to_fork)
	{
		--cmds[(*i)]-> to_fork;
		--cmds[(*i)]-> p_open;
		data -> subshell = fork();
		if (data -> subshell == -1)
			print_err_and_exit(data, NULL, "bash", 1);
		if (data -> subshell == 0)
			executing(data, &cmds[(*i)], 1);
		++cmds[(*i)]-> p_open;
		if (subshell == 0)
			(*i) += end_cmd_par(&cmds[(*i)], subshell);
		else if (subshell == 1)
			(*i) += find_next_cmd(data, &cmds[(*i)]);
		return (1);
	}
	return (0);
}
