/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/12 15:29:31 by dtoure           ###   ########.fr       */
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
				execve(cmd -> paths[i], cmd -> args, cmd -> data -> envp);
		}
		print_err_and_exit(cmd -> data, cmd, "bash: ", 1);
	}
	else
	{
		if (access(cmd -> cmd, X_OK) != -1)
			execve(cmd -> cmd, cmd -> args, cmd -> data -> envp);
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
	free_all(cmd -> data, 0, 1);
}

void	executing(t_data *data, t_cmd **cmds, int subshell)
{
	int		i;
	pid_t	pid_ret;
	int		res;
	
	i = -1;
	cmds[0]-> p_open = cmds[0]-> to_fork + (subshell == 1);
	while (cmds[++i])
	{
		res = prepare_next_step(cmds, cmds[i]-> stop, &i, subshell);
		if (res == 0 && is_subshell(data, cmds, &i, subshell) == 0)
		{
			data -> p_num += cmds[i]-> p_open + cmds[i]-> p_close;
			pid_ret = fork();
			if (pid_ret < 0)
				print_err_and_exit(data, NULL, "bash", 1);
			if (pid_ret == 0)
				forking(cmds, i);
			cmds[i]-> pid = pid_ret;
			handle_pipes(data);
			i -= (cmds[i] == NULL);
		}
		if (subshell && data -> p_num == 0)
			break ;
	}
	wait_all_child(data, cmds, subshell);
}
