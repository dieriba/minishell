/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/02 03:57:54 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_exec_or_not(t_cmd *cmd, int ex_status, int status, int opt)
{
	if (WIFSIGNALED(ex_status))
		return (-1);
	if (opt && (cmd -> prev_cmd -> built_in && cmd -> prev_cmd -> executed))
	{	
		cmd -> data -> last_exec_stat = cmd -> prev_cmd -> exit_status;
		status = cmd -> data -> last_exec_stat;
	}
	if (!ft_strcmp("&&", cmd -> prev_stop) && status == 0)
	{
		cmd -> executed = 1;
		return (0);
	}
	else if (!ft_strcmp("&&", cmd -> prev_stop))
		return (1);
	else if (!ft_strcmp("||", cmd -> prev_stop) && status == 0)
		return (1);
	else
	{
		cmd -> executed = 1;
		return (0);
	}
}

void	wait_command_before(t_cmd **cmds, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (cmds[++i])
	{
		if (cmds[i + 1] == cmd)
			break ;
		if (ft_strcmp(cmds[i]-> prev_stop, "|"))
			j = i;
	}
	if (j < 0)
		return ;
	while (j < i)
	{
		if (!cmds[j]-> waited && !cmds[j]-> built_in)
		{
			if (waitpid(cmds[j]-> pid, &cmds[j]-> exit_status, 0) < 0
				&& errno != ECHILD)
				print_err_and_exit(cmd -> data, NULL, "Error with waitpid", 1);
			cmds[j]-> waited = 1;
		}
		j++;
	}
}

int	get_status(t_data *data, t_cmd *cmd, pid_t pid_ret, char *stop)
{
	int	status;
	int	pipes;

	status = 0;
	pipes = ft_strcmp("|", stop);
	if (pipes == 0)
		status = pipe_exec(cmd -> prev_cmd);
	if ((!status && pid_ret) && pipes)
	{
		cmd -> prev_cmd -> waited = 1;
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			data -> status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data -> status = status;
		cmd -> prev_cmd -> exit_status = status;
		data -> last_exec_stat = (data -> status > 0);
		status = to_exec_or_not(cmd, status, data -> status, 0);
	}
	else if (!status)
		status = to_exec_or_not(cmd, status, data -> last_exec_stat, 1);
	return (status);
}

int	prepare_next_step(t_data *data, t_cmd **cmds, char *stop, int *i)
{
	int			status;
	t_cmd		*next_cmd;

	next_cmd = cmds[*i + 1];
	status = 0;
	if ((*i) > 0 && cmds[(*i) - 1]-> p_close)
	{
		status = get_status(
				data, cmds[(*i)], data -> subshell_pid, cmds[(*i)]-> prev_stop);
		data -> subshell_pid = 0;
	}
	else if ((*i) > 0)
		status = get_status(
				data, cmds[(*i)], cmds[(*i) - 1]-> pid, cmds[(*i)]-> prev_stop);
	if ((!status && !cmds[(*i)]-> to_fork)
		&& ((!cmds[(*i)]-> p_close
				&& !ft_strcmp("|", stop)) && (next_cmd && !next_cmd -> p_open)))
		init_pipes(data, data -> pipes, &data -> inited);
	else if (!status)
		init_s_pipes(cmds, (*i), ft_strcmp("|", stop), pipe_par(&cmds[(*i)]));
	if (status > 0 && cmds[(*i)]-> p_open)
		(*i) = end_cmd_par(cmds, *i);
	return (status);
}
