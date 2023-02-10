/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:58:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 04:09:16 by dtoure           ###   ########.fr       */
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

int	verify_cmd(t_data *data, t_cmd *cmd)
{
	if (cmd -> to_not_exec)
	{
		data -> status = 1;
		data -> last_exec_stat = 1;
		return (1);
	}
	if (cmd -> to_not_calloc == 0)
	{
		clean_files(cmd);
		clean_cmd(cmd);
	}
	return (0);
}

void	forking(t_cmd *cmd)
{
	struct sigaction	ctrl_c;
	struct sigaction	sigquit;
	
	g_collector = ft_calloc(sizeof(t_collector), 1);
	is_error(cmd -> data, g_collector, MALLOC_ERR, 0);
	g_collector -> data = cmd;
	ctrl_c.sa_flags = 0;
	ctrl_c.sa_handler = SIG_DFL;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
	sigquit.sa_flags = SA_RESTART;
	sigquit.sa_handler = exit_dumped;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
	set_redirections_files(cmd);
	if (cmd -> built_in == 0)
		run_cmd(cmd);
	free_all(cmd -> data, cmd -> data -> status);
}

void	execute_routine(t_data *data, t_cmd *cmd)
{
	pid_t	pid_ret;

	if (data -> s_pipes && !ft_strcmp(cmd -> prev_stop, "|")
		&& cmd -> prev_cmd -> p_close)
		close_fd(data, "bash", &data -> s_pipes -> s_pipes[1]);
	if (!built_in(data, cmd, 0))
	{
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(data, NULL, "bash", 1);
		if (pid_ret == 0)
			forking(cmd);
		cmd -> pid = pid_ret;
	}
	handle_pipes(data, cmd);
}

void	executing(t_data *data, t_cmd **cmds)
{
	int		i;
	int		res;

	i = -1;
	if (cmds[0]-> p_open && !cmds[0]-> to_fork)
		cmds[0]-> p_open = 1;
	else if (cmds[0]-> p_open)
		cmds[0]-> p_open = cmds[0]-> to_fork;
	while (cmds[++i])
	{
		if (verify_cmd(data, cmds[i]))
			continue ;
		is_built_in(cmds[i]);
		res = prepare_next_step(data, cmds, cmds[i]-> stop, &i);
		if (res == 0 && is_subshell(data, cmds, &i) == 0)
			execute_routine(data, cmds[i]);
		if (cmds[i] == NULL
			|| ((data -> subshell && cmds[i + 1]) && cmds[i + 1]-> break_cmd))
			break ;
	}
	clean_s_pipes(data);
	wait_all_child(data, cmds);
}
