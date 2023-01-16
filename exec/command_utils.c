/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/16 02:45:04 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_exec_or_not(char *stop, int status)
{	
	if (!ft_strcmp("&&", stop) && status == 0)
		return (0);
	else if (!ft_strcmp("&&", stop))
		return (1);
	else if (!ft_strcmp("||", stop) && status == 0)
		return (1);
	else
		return (0);
}

int	pipe_exec(t_cmd *cmd)
{
	if (cmd -> p_close && cmd -> data -> subshell_pid)
		return (0);
	else if (cmd -> p_close && cmd -> data -> subshell_pid == 0)
		return (1);
	else if (cmd -> pid)
		return (0);
	else
		return (1);
}

int	get_status(t_data *data, t_cmd *cmd, pid_t pid_ret, char *stop)
{
	int	status;

	if (ft_strcmp("|", stop) == 0)
		return (pipe_exec(cmd -> prev_cmd));
	status = 0;
	if (pid_ret)
	{
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			data -> status = WEXITSTATUS(status);
		data -> last_exec_stat = (data -> status > 0);
		status = to_exec_or_not(stop, data -> status);
	}
	else
		status = to_exec_or_not(stop, data -> last_exec_stat);
	return (status);
}

void	init_s_pipes(t_data *data)
{
	if (data -> s_pipes_inited == 0)
		init_pipes(data, data -> sub_pipes[0], &data -> s_pipes_inited, 1);
	else
		init_pipes(data, data -> sub_pipes[1], &data -> s_pipes_inited, 1);
}

int	prepare_next_step(t_cmd **cmds, char *stop, int *i)
{
	int			status;
	t_data		*data;
	
	data = cmds[0]-> data;
	status = 0;
	if ((*i) > 0 && cmds[(*i) - 1]-> p_close)
	{
		status = get_status(data, cmds[(*i)], data -> subshell_pid, cmds[(*i)]-> prev_stop);
		data -> subshell_pid = 0;
	}
	else if ((*i) > 0)
		status = get_status(data, cmds[(*i)], cmds[(*i) - 1]-> pid, cmds[(*i)]-> prev_stop);
	if (!status && cmds[(*i)]-> to_fork == 0 && cmds[(*i)]-> p_close == 0 && !ft_strcmp("|", stop))
		init_pipes(data, data -> pipes, &data -> inited, 0);
	else if (status == 0 && pipe_par(&cmds[(*i)]) == 0)
		init_s_pipes(data);
	if (status && cmds[(*i)]-> p_open)
		(*i) += end_cmd_par(&cmds[(*i)], 0);
	else if (status && cmds[(*i)]-> p_close)
		data -> p_num += cmds[(*i)]-> p_close;
	return (status);
}
