/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 17:37:42 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd -> cmd == NULL)
		return ;
	i = -1;
	if (cmd -> no_path)
	{
		while (cmd -> paths[++i])
		{
			if (access(cmd -> paths[i], X_OK) != -1)
				execve(cmd -> paths[i], cmd -> args, NULL);
		}
		print_err_and_exit(cmd -> data, cmd, "bash: ", 1);
	}
	else
	{
		if (access(cmd -> cmd, X_OK) != -1)
			execve(cmd -> cmd, cmd -> args, NULL);
		print_err_and_exit(cmd -> data, cmd, "bash: ", 1);
	}
}

void	handle_pipes(t_data *data)
{
	if (data -> prev_pipes > 0)
	{
		close_fd(data, "bash error", data -> prev_pipes);
		data -> prev_pipes = -1;
	}
	if (data -> inited)
	{
		data -> prev_pipes = data -> pipes[0];
		close_fd(data, "bash pipes close", data -> pipes[1]);
	}
	data -> inited = 0;
}

void	forking(t_cmd **cmds, int i)
{
	char	*prev;
	t_cmd	*cmd;

	cmd = cmds[i];
	if (i > 0)
		prev = cmds[--i]-> stop;
	else
		prev = NULL;
	set_redirections_files(cmd, prev);
	run_cmd(cmd);
}

void	executing(t_data *data, t_cmd **cmds)
{
	int		i;
	pid_t	pid_ret;
	int		p_num;
	char	*stop;

	i = -1;
	while (cmds[++i])
	{
		p_num = find_cmd_in_par(cmds, cmds[i], i);
		stop = find_lim_par(cmds, p_num, i);
		if (prepare_next_step(cmds, stop, i))
			continue ;
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(data, NULL, "bash", 1);
		if (pid_ret == 0)
			forking(cmds, i);
		cmds[i]-> pid = pid_ret;
		handle_pipes(data);
	}
	wait_all_child(data, cmds);
}
