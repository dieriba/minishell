/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/12 15:04:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_child(t_data *data, t_cmd **cmds, int subshell)
{
	size_t	i;
	int		status;

	i = -1;
	status = 0;
	close_all_pipes(data, &data -> here_docs, 1, 0);
	data -> here_doc_closed = 1;
	while (cmds[++i])
	{
		if (cmds[i]-> pid && waitpid(cmds[i]-> pid, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
	if (data -> subshell)
		if (waitpid(data -> subshell, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	if (WIFEXITED(status))
		data -> status = WEXITSTATUS(status);
	if (subshell)
		exit(data -> status);
}
