/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/07 22:05:32 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_child(t_data *data, t_cmd **cmds)
{
	size_t	i;
	int		status;

	i = -1;
	status = 0;
	close_all_pipes(data, &data -> here_docs, 1, 0);
	data -> here_doc_closed = 1;
	while (cmds[++i])
	{
		if (waitpid(cmds[i]-> pid, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
	if (WIFEXITED(status))
		data -> status = WEXITSTATUS(status);
}
