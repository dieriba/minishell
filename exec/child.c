/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:45:46 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_through_child(t_data *data, t_cmd **cmds, int *status)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> pid && waitpid(
				cmds[i]-> pid, status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
	if (data -> subshell_pid)
	{
		if (waitpid(data -> subshell_pid,
				status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
}

void	wait_all_child(t_data *data, t_cmd **cmds)
{
	int	status;

	status = 0;
	ignore_signals();
	close_all_pipes(data, &data -> here_docs, 1, 0);
	loop_through_child(data, cmds, &status);
	if (WIFEXITED(status))
		data -> status = WEXITSTATUS(status);
	handle_signals();
	if (data -> subshell)
		free_all(data, data -> status);
}
