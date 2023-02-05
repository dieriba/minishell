/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/05 21:38:18 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_subshell(t_data *data, t_cmd **cmds, int *i)
{
	int		j;

	if (cmds[(*i)]-> to_fork)
	{
		//printf("Commande : %s\n", cmds[(*i)]-> args[0]);
		j = end_cmd_par(cmds, *i);
		//printf("Commande : %s J value : %d subshell : %d\n", cmds[(*i)]-> args[0], j, data -> subshell);
		if (cmds[j] && cmds[j + 1])
			cmds[j + 1]-> break_cmd = 1;
		--cmds[(*i)]-> to_fork;
		data -> subshell++;
		data -> subshell_pid = fork();
		cmds[(*i)]-> pid = data -> subshell_pid;
		if (data -> subshell_pid == -1)
			print_err_and_exit(data, NULL, "bash", 1);
		if (data -> subshell_pid == 0)
			executing(data, &cmds[(*i)]);
		data -> subshell--;
		(*i) = j;
		if (cmds[j] && cmds[j + 1])
			cmds[j + 1]-> break_cmd = 0;
		//printf("J value : %d\n", j);
		//if (cmds[j])
			//printf("Move Subshelll value : %d commande : %s args : %s\n", data -> subshell, cmds[j]-> args[0], cmds[j]-> args[1]);
		return (1);
	}
	return (0);
}
