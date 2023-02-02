/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/02 20:01:52 by dtoure           ###   ########.fr       */
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
		print_err_and_exit(cmd -> data, cmd, "bash", 1);
	}
	else
	{
		if (access(cmd -> cmd, X_OK) != -1)
			execve(cmd -> cmd, cmd -> args, cmd -> data -> envp);
		print_err_and_exit(cmd -> data, cmd, "bash", 1);
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
	if (data -> s_pipes_inited
		&& subshell == 0 && cmd -> prev_cmd && cmd -> prev_cmd -> p_close)
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
	g_collector = ft_calloc(sizeof(t_collector), 1);
	is_error(cmd -> data, g_collector, MALLOC_ERR, 0);
	g_collector -> data = cmd;
	cmd -> data -> ctrl_c.sa_handler = SIG_DFL;
	sigaction(SIGINT, &cmd -> data -> ctrl_c, NULL);
	cmd -> data -> sigquit.sa_flags = SA_RESTART;
	cmd -> data -> sigquit.sa_handler = exit_dumped;
	sigemptyset(&cmd -> data -> sigquit.sa_mask);
	sigaction(SIGQUIT, &cmd -> data -> sigquit, NULL);
	set_redirections_files(cmd, prev, subshell);
	if (cmd -> built_in == 0)
		run_cmd(cmd);
	free_all(cmd -> data, cmd -> data -> status);
}

void	execute_routine(t_data *data, t_cmd **cmds, int i, int subshell)
{
	pid_t	pid_ret;

	data -> p_num += cmds[i]-> p_open + cmds[i]-> p_close;
	if (!built_in(data, cmds[i], subshell, 0))
	{
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(data, NULL, "bash", 1);
		if (pid_ret == 0)
			forking(cmds, subshell, i);
		cmds[i]-> pid = pid_ret;
	}
	handle_pipes(data, cmds[i], subshell);
}

void	executing(t_data *data, t_cmd **cmds, int subshell)
{
	int		i;
	int		res;

	i = -1;
	cmds[0]-> p_open = cmds[0]-> to_fork + (subshell == 1);
	close_sub_pipes(data, subshell);
	while (cmds[++i])
	{
		if (cmds[i]-> to_not_exec)
		{
			data -> status = 1;
			data -> last_exec_stat = 1;
			continue ;
		}
		if (cmds[i]-> to_not_calloc == 0)
		{
			clean_files(cmds[i]);
			clean_cmd(cmds[i]);
		}
		is_built_in(cmds[i]);
		res = prepare_next_step(data, cmds, cmds[i]-> stop, &i);
		if (res == 0 && is_subshell(data, cmds, &i, subshell) == 0)
			execute_routine(data, cmds, i, subshell);
		if ((subshell && data -> p_num == 0) || cmds[i] == NULL)
			break ;
	}
	wait_all_child(data, cmds, subshell);
}
