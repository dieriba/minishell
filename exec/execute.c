/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 20:29:46 by dtoure           ###   ########.fr       */
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

void	handle_pipes(t_data *data, t_cmd *cmd, int subshell)
{
	close_fd(data, "bash error", &data -> prev_pipes);
	if (data -> inited)
	{
		data -> prev_pipes = data -> pipes[0];
		close_fd(data, "bash pipes close", &data -> pipes[1]);
	}
	if (data -> s_pipes_inited && subshell == 0 && cmd -> prev_cmd && cmd -> prev_cmd -> p_close)
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	else if (data -> s_pipes_inited && subshell && cmd -> p_close)
	{
		close_one_end(data, data -> p_pipes, 1, &data -> s_pipes_inited);
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	}
	data -> inited = 0;
}

void	forking(t_cmd **cmds, int subshell, int i)
{
	char	*prev;
	t_cmd	*cmd;
	
	cmd = cmds[i];
	if (i > 0)
		prev = cmds[--i]-> stop;
	else
		prev = NULL;
	set_redirections_files(cmd, prev, subshell);
	if (is_not_built_in(cmd -> cmd))
		run_cmd(cmd);
	free_all(cmd -> data, cmd -> data -> status);
}

void	executing(t_data *data, t_cmd **cmds, int subshell)
{
	int		i;
	pid_t	pid_ret;
	int		res;
	
	i = -1;
	cmds[0]-> p_open = cmds[0]-> to_fork + (subshell == 1);
	close_sub_pipes(data, subshell);
	while (cmds[++i])
	{
		clean_files(cmds[i]);
		clean_cmd(cmds[i]);
		res = prepare_next_step(cmds, cmds[i]-> stop, &i);
		if (res == 0 && is_subshell(data, cmds, &i, subshell) == 0)
		{
			data -> p_num += cmds[i]-> p_open + cmds[i]-> p_close;
			built_in(data, cmds[i], subshell, 0);
			pid_ret = fork();
			if (pid_ret < 0)
				print_err_and_exit(data, NULL, "bash", 1);
			if (pid_ret == 0)
				forking(cmds, subshell, i);
			cmds[i]-> pid = pid_ret;
			handle_pipes(data, cmds[i], subshell);
			i -= (cmds[i] == NULL);
		}
		if (subshell && data -> p_num == 0)
			break ;
	}
	wait_all_child(data, cmds, subshell);
}
