/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 04:21:06 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	forking(t_cmd **cmds, int i)
{
	t_cmd 	*cmd;
	char	*prev;

	cmd = cmds[i];
	if (i > 0)
		prev = cmds[--i]-> stop;
	set_redirections_files(cmd, prev);
	run_cmd(cmd);
}

void	piping()
{
	int		i;
	t_cmd	**cmds;
	pid_t	pid_ret;
	int		p_num;
	char	*stop;

	cmds = data -> cmds;
	i = -1;
	pid_ret = 0;
	while (cmds[++i])
	{
		p_num = find_cmd_in_par(cmds, cmds[i], i);
		stop = find_lim_par(cmds, cmds[i], i);
		prepare_next_step(stop, cmds[i]-> stop, pid_ret);
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(NULL, "bash", 1);
		if (pid_ret == 0)
			forking(cmds, i);
		cmds[i]-> pid = pid_ret;
		if (close(data -> pipes[1]) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
	wait_all_child(cmds);
}
