/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 23:21:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_all_child(t_cmd **cmds)
{
	size_t	i;
	int		status;

	i = -1;
	while (cmds[++i])
	{
		if (waitpid(cmds[i]-> pid, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(NULL, "Error with waitpid", 1);
	}
	if (WIFEXITED(status))
		g_data -> status = WEXITSTATUS(status);
}
