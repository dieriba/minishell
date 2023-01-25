/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 03:25:28 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_child(t_data *data, t_cmd **cmds, int subshell)
{
	size_t	i;

	i = -1;
	close_all_pipes(data, &data -> here_docs, 1, 0);
	while (cmds[++i])
	{
		if (cmds[i]-> pid && waitpid(cmds[i]-> pid, &data -> status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
	if (data -> subshell_pid)
		if (waitpid(data -> subshell_pid, &data -> status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	if (WIFEXITED(data -> status))
		data -> status = WEXITSTATUS(data -> status);
	if (subshell)
		free_all(data, data -> status);
}
