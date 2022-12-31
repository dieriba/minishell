/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 09:51:59 by dtoure           ###   ########.fr       */
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
	else 
		prev = NULL;
	set_redirections_files(cmd, prev);
	run_cmd(cmd);
}

void	executing(t_cmd **cmds)
{
	int		i;
	pid_t	pid_ret;
	int		p_num;
	char	*stop;

	i = -1;
	data -> prev_pipes = -1;
	while (cmds[++i])
	{
		p_num = find_cmd_in_par(cmds, cmds[i], i);
		stop = find_lim_par(cmds, p_num, i);
		prepare_next_step(cmds, stop, i, pid_ret);
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(NULL, "bash", 1);
		if (pid_ret == 0)
			forking(cmds, i);
		cmds[i]-> pid = pid_ret;
		if (data -> prev_pipes > 0)
			close_fd("bash", data -> prev_pipes);
		if (data -> inited)
		{
			data -> prev_pipes = data -> pipes[0];
			close_fd("bash", data -> pipes[1]);
		}
		else
			data -> prev_pipes = -1;
		data -> inited = 0;
	}
	wait_all_child(cmds);
}
