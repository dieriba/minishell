/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 00:31:57 by dtoure           ###   ########.fr       */
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
	else if (cmd -> pid || cmd -> built_in)
		return (0);
	else
		return (1);
}

int	get_status(t_data *data, t_cmd *cmd, pid_t pid_ret, char *stop)
{
	int	status;
	int	pipes;

	status = 0;
	pipes = ft_strcmp("|", stop);
	if (pipes == 0)
		status = pipe_exec(cmd -> prev_cmd);
	if (((!status && pid_ret) && pipes))
	{
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			data -> status = WEXITSTATUS(status);
		data -> last_exec_stat = (data -> status > 0);
		status = to_exec_or_not(stop, data -> status);
	}
	else if (!status)
		status = to_exec_or_not(stop, data -> last_exec_stat);
	return (status);
}

void	init_s_pipes(t_data *data, t_cmd *cmd)
{
	t_s_pipes	*node;

	node = ft_calloc(sizeof(t_s_pipes), 1);
	is_error(data, node, MALLOC_ERR, 0);
	node -> subshell[0] = data -> subshell;
	node -> subshell[1] = data -> subshell + 1;
	if (pipe(node -> s_pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
	node -> read_end = node;
	if (data -> s_pipes
		&& !ft_strcmp(cmd -> prev_stop, "|") && cmd -> prev_cmd -> p_close)
		node -> read_end = data -> s_pipes;
	if (data -> s_pipes == NULL)
		data -> s_pipes = node;
	else
	{
		node -> next = data -> s_pipes;
		data -> s_pipes = node;
	}
}

int	prepare_next_step(t_data *data, t_cmd **cmds, char *stop, int *i)
{
	int			status;

	status = 0;
	if ((*i) > 0 && cmds[(*i) - 1]-> p_close)
	{
		status = get_status(
				data, cmds[(*i)], data -> subshell_pid, cmds[(*i)]-> prev_stop);
	}
	else if ((*i) > 0)
		status = get_status(
				data, cmds[(*i)], cmds[(*i) - 1]-> pid, cmds[(*i)]-> prev_stop);
	if (!status && cmds[(*i)]-> to_fork == 0
		&& cmds[(*i)]-> p_close == 0 && !ft_strcmp("|", stop))
		init_pipes(data, data -> pipes, &data -> inited);
	else if (status == 0 && pipe_par(&cmds[(*i)]) == 0)
		init_s_pipes(data, cmds[(*i)]);
	if (status && cmds[(*i)]-> p_open)
		(*i) = end_cmd_par(cmds, *i);
	return (status);
}
